#include "gfx/backend/vulkan/BackendVK.hpp"
#include "gfx/backend/vulkan/Renderer.hpp"
#include "gfx/backend/vulkan/Shader.hpp"
#include "gfx/backend/vulkan/Mesh.hpp"
#include "gfx/backend/vulkan/Image.hpp"
#include "gfx/backend/vulkan/Buffer.hpp"
#include "gfx/backend/vulkan/Swapchain.hpp"

#include "gfx/backend/vulkan/PipelineLayout.hpp"
#include "gfx/backend/vulkan/Pipeline.hpp"

#include "gfx/backend/vulkan/BindGroupLayout.hpp"
#include "gfx/backend/vulkan/BindGroup.hpp"
#include "gfx/backend/vulkan/Descriptors.hpp"

namespace gfx::vk 
{

BackendVK::BackendVK(Window* windowInstance) : 
    Device(BackendType::Vulkan), 
    window(windowInstance), 
    device(window),
    renderer(device, window, SwapchainDesc{})
{
    descriptorPoolManager = DescriptorPoolManager::Builder(device)
		.setMaxSets(1024)
		.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1024)
		.addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1024)
		.addPoolSize(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1024)
		.build();
}

void BackendVK::updateSwapchain(const SwapchainDesc& desc)
{
    renderer.updateSwapchain(desc);
}

Handle<BindGroupLayout> BackendVK::createBindGroupLayout(const BindGroupLayoutDesc& desc)
{
    return bindGroupLayouts.Create(device, desc);
}

Handle<BindGroup> BackendVK::createBindGroup      (Handle<BindGroupLayout> bindGroupLayout)
{
    return bindGroups.Create(
            device,
            *reinterpret_cast<BindGroupLayoutVK*>(bindGroupLayout.Get()),
            *descriptorPoolManager.get());
}

Handle<Sampler> BackendVK::createSampler(const SamplerDesc& desc)
{
    return samplers.Create(device, desc);
}

Handle<Image> BackendVK::createImage(const ImageDesc& desc)
{
    return images.Create(device, desc);
}

Handle<Buffer> BackendVK::createBuffer(const BufferDesc& desc) 
{
    return buffers.Create(device, desc);
}

Handle<Shader> BackendVK::createShader(const ShaderDesc& desc) 
{
    return shaders.Create(device, desc);
}

Handle<PipelineLayout> BackendVK::createPipelineLayout(const PipelineLayoutDesc& desc)
{
    return pipelineLayouts.Create(device, desc);
}

Handle<RenderPipeline> BackendVK::createRenderPipeline(const RenderPipelineDesc& desc)
{
    return renderPipelines.Create(device, desc);
}

Handle<Mesh> BackendVK::createMesh(const MeshDesc& desc) 
{
    return meshes.Create(device, desc);
}


BackendVK::~BackendVK()
{
   vkDeviceWaitIdle(device.device()); 
}

}
