#include "gfx/backend/vulkan/BackendVK.hpp"
#include "gfx/backend/vulkan/Shader.hpp"
#include "gfx/backend/vulkan/Mesh.hpp"

#include "gfx/backend/vulkan/PipelineLayout.hpp"
#include "gfx/backend/vulkan/Pipeline.hpp"

namespace gfx::vk 
{

BackendVK::BackendVK(Window* windowInstance) : 
    Device(BackendType::Vulkan), 
    window(windowInstance), 
    device(window),
    renderer(device, window)
{
    std::cout << "Backend successfully initialized." << std::endl;
}

Handle<Shader> BackendVK::createShader(const ShaderDesc& desc) 
{
    return shaders.Create(device, desc);
};

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
