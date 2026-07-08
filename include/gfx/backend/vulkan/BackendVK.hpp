#pragma once

#include "gfx/IDevice.hpp"
#include "gfx/ResourceManager.hpp"

#include "Window.hpp"
#include "Device.hpp"
#include "Renderer.hpp"

struct Window;

namespace gfx
{
    struct Framebuffer;
}

namespace gfx::vk 
{

struct BufferVK;
struct SamplerVK;
struct ImageVK;
struct MeshVK;
struct ShaderVK;
struct PipelineLayoutVK;
struct RenderPipelineVK;
struct BindGroupLayoutVK;
struct BindGroupVK;

struct DescriptorPoolManager;

struct BackendVK : public gfx::Device
{
    BackendVK(Window* windowInstance);
    ~BackendVK();

    Handle<Sampler>        createSampler(const SamplerDesc& desc) override;
    Handle<Image>          createImage (const ImageDesc& desc)    override;
    Handle<Buffer>         createBuffer(const BufferDesc& desc)   override;

    Handle<Mesh>           createMesh    (const MeshDesc& desc) override;

    Handle<Shader>         createShader(const ShaderDesc& desc) override;

    Handle<BindGroupLayout> createBindGroupLayout(const BindGroupLayoutDesc& desc) override;
    Handle<BindGroup>       createBindGroup      (Handle<BindGroupLayout> bindGroupLayout) override;

    Handle<Framebuffer>    createFramebuffer     (const FramebufferDesc& desc) override{return {};};
    Handle<RenderPass>     createRenderPass      (const RenderPassDesc& desc)  override{return {};};

    Handle<PipelineLayout> createPipelineLayout  (const PipelineLayoutDesc& desc) override;
    Handle<RenderPipeline> createRenderPipeline  (const RenderPipelineDesc& desc) override;

    void updateSwapchain(const gfx::SwapchainDesc& desc) override;

    ResourceManager<BufferVK> buffers;
    ResourceManager<SamplerVK>samplers;
    ResourceManager<ImageVK>  images;
    ResourceManager<MeshVK>   meshes; 
    ResourceManager<ShaderVK> shaders;
    ResourceManager<PipelineLayoutVK> pipelineLayouts;
    ResourceManager<RenderPipelineVK> renderPipelines;

    ResourceManager<BindGroupLayoutVK> bindGroupLayouts;
    ResourceManager<BindGroupVK>       bindGroups;

    WindowVK window;
    DeviceVK device;
    
    RendererVK renderer;
    std::unique_ptr<DescriptorPoolManager> descriptorPoolManager;
};

}
