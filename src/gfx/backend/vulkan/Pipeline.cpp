#include "gfx/backend/vulkan/Pipeline.hpp"
#include "gfx/backend/vulkan/Device.hpp"
#include "gfx/backend/vulkan/Convert.hpp"
#include "gfx/backend/vulkan/PipelineLayout.hpp"
#include "gfx/backend/vulkan/Shader.hpp"
#include "gfx/backend/vulkan/Vertex.hpp"

namespace gfx::vk 
{

struct PipelineConfigInfo {
    VkPipelineViewportStateCreateInfo                viewportInfo;
    VkPipelineInputAssemblyStateCreateInfo           inputAssemblyInfo;
    VkPipelineRasterizationStateCreateInfo           rasterizationInfo;
    VkPipelineMultisampleStateCreateInfo             multisampleInfo;
    std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments;
    VkPipelineColorBlendStateCreateInfo              colorBlendInfo;
    VkPipelineDepthStencilStateCreateInfo            depthStencilInfo;
    std::vector<VkDynamicState>                      dynamicStateEnables;
    VkPipelineDynamicStateCreateInfo                 dynamicStateInfo;
    VkPipelineLayout                                 pipelineLayout = nullptr;
    uint32_t                                         subpass = 0;
};

inline void loadPipelineConfig(PipelineConfigInfo& configInfo, const PipelineState& state)
{
    using namespace vk_convert;

    // --- Input assembly ---
    configInfo.inputAssemblyInfo = {};
    configInfo.inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    configInfo.inputAssemblyInfo.topology = ToVk(state.topology);
    configInfo.inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

    // --- Rasterization ---
    const RasterState& r = state.raster;
    configInfo.rasterizationInfo = {};
    configInfo.rasterizationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    configInfo.rasterizationInfo.depthClampEnable        = r.depthClampEnable;
    configInfo.rasterizationInfo.rasterizerDiscardEnable = r.rasterizerDiscard;
    configInfo.rasterizationInfo.polygonMode             = ToVk(r.fill);
    configInfo.rasterizationInfo.lineWidth               = r.lineWidth;
    configInfo.rasterizationInfo.cullMode                = ToVk(r.cull);
    configInfo.rasterizationInfo.frontFace               = ToVk(r.frontFace);
    configInfo.rasterizationInfo.depthBiasEnable         = r.depthBias.enable;
    configInfo.rasterizationInfo.depthBiasConstantFactor = r.depthBias.constantFactor;
    configInfo.rasterizationInfo.depthBiasClamp          = r.depthBias.clamp;
    configInfo.rasterizationInfo.depthBiasSlopeFactor    = r.depthBias.slopeFactor;

    // --- Multisample ---
    const MultisampleState& ms = state.multisample;
    configInfo.multisampleInfo = {};
    configInfo.multisampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    configInfo.multisampleInfo.rasterizationSamples  = ToVk(ms.sampleCount);
    configInfo.multisampleInfo.sampleShadingEnable   = ms.sampleShadingEnable;
    configInfo.multisampleInfo.minSampleShading      = ms.minSampleShading;
    configInfo.multisampleInfo.alphaToCoverageEnable = ms.alphaToCoverage;
    configInfo.multisampleInfo.alphaToOneEnable      = ms.alphaToOne;
    static VkSampleMask sampleMaskStorage;
    sampleMaskStorage = static_cast<VkSampleMask>(ms.sampleMask & 0xFFFFFFFFu);
    configInfo.multisampleInfo.pSampleMask = &sampleMaskStorage;

    // --- Color blend ---
    const BlendState& b = state.blend;
    configInfo.colorBlendAttachments.clear();
    configInfo.colorBlendAttachments.resize(b.attachmentCount);
    for (uint32_t i = 0; i < b.attachmentCount; ++i)
    {
        const BlendAttachmentState& src = b.attachments[i];
        VkPipelineColorBlendAttachmentState& dst = configInfo.colorBlendAttachments[i];
        dst = {};
        dst.blendEnable         = src.enabled;
        dst.srcColorBlendFactor = ToVk(src.srcColor);
        dst.dstColorBlendFactor = ToVk(src.dstColor);
        dst.colorBlendOp        = ToVk(src.colorOp);
        dst.srcAlphaBlendFactor = ToVk(src.srcAlpha);
        dst.dstAlphaBlendFactor = ToVk(src.dstAlpha);
        dst.alphaBlendOp        = ToVk(src.alphaOp);
        dst.colorWriteMask      = ToVk(src.writeMask);
    }

    configInfo.colorBlendInfo = {};
    configInfo.colorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    configInfo.colorBlendInfo.logicOpEnable     = b.logicOpEnable;
    configInfo.colorBlendInfo.logicOp           = ToVk(b.logicOp);
    configInfo.colorBlendInfo.attachmentCount   = static_cast<uint32_t>(configInfo.colorBlendAttachments.size());
    configInfo.colorBlendInfo.pAttachments      = configInfo.colorBlendAttachments.data();
    for (int i = 0; i < 4; ++i)
        configInfo.colorBlendInfo.blendConstants[i] = b.blendConstants[i];

    // --- Depth / Stencil ---
    const DepthState& d = state.depth;
    configInfo.depthStencilInfo = {};
    configInfo.depthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    configInfo.depthStencilInfo.depthTestEnable       = d.testEnable;
    configInfo.depthStencilInfo.depthWriteEnable      = d.writeEnable;
    configInfo.depthStencilInfo.depthCompareOp        = ToVk(d.compareOp);
    configInfo.depthStencilInfo.depthBoundsTestEnable = d.boundsEnable;
    configInfo.depthStencilInfo.minDepthBounds        = d.minBounds;
    configInfo.depthStencilInfo.maxDepthBounds        = d.maxBounds;
    configInfo.depthStencilInfo.stencilTestEnable     = d.stencilEnable;
    configInfo.depthStencilInfo.front                 = ToVk(d.front);
    configInfo.depthStencilInfo.back                  = ToVk(d.back);

    // --- Viewport ---
    configInfo.viewportInfo = {};
    configInfo.viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    configInfo.viewportInfo.viewportCount = 1;
    configInfo.viewportInfo.pViewports    = nullptr;
    configInfo.viewportInfo.scissorCount  = 1;
    configInfo.viewportInfo.pScissors     = nullptr;

    // --- Dynamic state ---
    configInfo.dynamicStateEnables = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
    if (r.depthBias.enable)
        configInfo.dynamicStateEnables.push_back(VK_DYNAMIC_STATE_DEPTH_BIAS);
    if (r.lineWidth != 1.0f)
        configInfo.dynamicStateEnables.push_back(VK_DYNAMIC_STATE_LINE_WIDTH);

    configInfo.dynamicStateInfo = {};
    configInfo.dynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    configInfo.dynamicStateInfo.dynamicStateCount = static_cast<uint32_t>(configInfo.dynamicStateEnables.size());
    configInfo.dynamicStateInfo.pDynamicStates    = configInfo.dynamicStateEnables.data();
}

RenderPipelineVK::RenderPipelineVK(DeviceVK& device, const RenderPipelineDesc& desc) : device(device)
{
    this->descriptor = desc;

    PipelineConfigInfo configInfo{};
    loadPipelineConfig(configInfo, desc.pipelineState);

    ShaderVK* vertShader = reinterpret_cast<ShaderVK*>(desc.vertexState.module.Get());
    ShaderVK* fragShader = reinterpret_cast<ShaderVK*>(desc.fragState.module.Get());

    VkPipelineShaderStageCreateInfo shaderStages[2];
    shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
	shaderStages[0].module = vertShader->getShaderModule();
	shaderStages[0].pName = "main";
	shaderStages[0].flags = 0;
	shaderStages[0].pNext = nullptr;
	shaderStages[0].pSpecializationInfo = nullptr;
	shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	shaderStages[1].module = fragShader->getShaderModule();
	shaderStages[1].pName = "main";
	shaderStages[1].flags = 0;
	shaderStages[1].pNext = nullptr;
	shaderStages[1].pSpecializationInfo = nullptr;

    auto bindings   = getBindingDescriptions  (desc.vertexState.layout);
    auto attributes = getAttributeDescriptions(desc.vertexState.layout);

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributes.size());
    vertexInputInfo.vertexBindingDescriptionCount   = static_cast<uint32_t>(bindings.size());
    vertexInputInfo.pVertexAttributeDescriptions    = attributes.data();
    vertexInputInfo.pVertexBindingDescriptions      = bindings.data();

    // --- Dynamic Rendering --- //
    VkFormat colorFormat = VK_FORMAT_B8G8R8A8_SRGB;
    VkFormat depthFormat = VK_FORMAT_D32_SFLOAT;

    VkPipelineRenderingCreateInfo renderingInfo{};
    renderingInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO;
    renderingInfo.colorAttachmentCount = 1;
    renderingInfo.pColorAttachmentFormats = &colorFormat;
    renderingInfo.depthAttachmentFormat = depthFormat;
    renderingInfo.stencilAttachmentFormat = VK_FORMAT_UNDEFINED;

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages             = shaderStages;
    pipelineInfo.pVertexInputState   = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &configInfo.inputAssemblyInfo;
    pipelineInfo.pViewportState      = &configInfo.viewportInfo;
    pipelineInfo.pRasterizationState = &configInfo.rasterizationInfo;
    pipelineInfo.pMultisampleState   = &configInfo.multisampleInfo;
    pipelineInfo.pColorBlendState    = &configInfo.colorBlendInfo;
    pipelineInfo.pDepthStencilState  = &configInfo.depthStencilInfo;
    pipelineInfo.pDynamicState       = &configInfo.dynamicStateInfo;
    pipelineInfo.pNext = &renderingInfo;

    VkPipelineLayout pipelineLayout = reinterpret_cast<PipelineLayoutVK*>(desc.pipelineLayout.Get())->getPipelineLayout();

    pipelineInfo.layout     = pipelineLayout;
    pipelineInfo.renderPass = VK_NULL_HANDLE;
    pipelineInfo.subpass    = 0;

    pipelineInfo.basePipelineIndex = -1;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

    if (vkCreateGraphicsPipelines(
			device.device(),
			VK_NULL_HANDLE,
			1,
			&pipelineInfo,
			nullptr,
			&graphicsPipeline) != VK_SUCCESS) {
			throw std::runtime_error("failed to create graphics pipeline");
		}
}

void RenderPipelineVK::bind(CommandBuffer cmdBuf)
{
    VkCommandBuffer commandBuffer = reinterpret_cast<VkCommandBuffer>(cmdBuf);
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
}

RenderPipelineVK::~RenderPipelineVK()
{
    device.getDeletionQueue().push_function([graphicsPipeline = this->graphicsPipeline, device = device.device()] {
        vkDestroyPipeline(device, graphicsPipeline, nullptr);
    });
}

}
