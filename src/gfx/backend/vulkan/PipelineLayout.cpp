#include "gfx/backend/vulkan/PipelineLayout.hpp"
#include "gfx/backend/vulkan/Device.hpp"

namespace gfx::vk 
{


PipelineLayoutVK::PipelineLayoutVK(DeviceVK& device, const PipelineLayoutDesc& desc) : device(device)
{
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	//pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(layouts_.size());
	//pipelineLayoutInfo.pSetLayouts = layouts_.data();
	if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
		VK_SUCCESS) {
		throw std::runtime_error("failed to create pipeline layout!");
	}
}

PipelineLayoutVK::~PipelineLayoutVK()
{
    device.getDeletionQueue().push_function([pipelineLayout = this->pipelineLayout, device = device.device()] {
        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    });
}

}
