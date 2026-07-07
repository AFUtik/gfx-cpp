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

struct MeshVK;
struct ShaderVK;
struct PipelineLayoutVK;
struct RenderPipelineVK;

struct BackendVK : public gfx::Device
{
    BackendVK(Window* windowInstance);
    ~BackendVK();

    Handle<Image>          createImage (const ImageDesc& desc)  override {return {};};
    Handle<Buffer>         createBuffer(const BufferDesc& desc) override {return {};};

    Handle<Mesh>           createMesh    (const MeshDesc& desc) override;

    Handle<Shader>         createShader(const ShaderDesc& desc) override;

    Handle<BindGroupLayout> createBindGroupLayout(const BindGroupLayoutDesc& desc) override{return {};};

    Handle<Framebuffer>    createFramebuffer     (const FramebufferDesc& desc) override{return {};};
    Handle<RenderPass>     createRenderPass      (const RenderPassDesc& desc)  override{return {};};

    Handle<PipelineLayout> createPipelineLayout  (const PipelineLayoutDesc& desc);
    Handle<RenderPipeline> createRenderPipeline  (const RenderPipelineDesc& desc);

    Framebuffer*    getScreenFramebuffer() override
    {
        return nullptr;
    }
    
    ResourceManager<MeshVK>   meshes; 
    ResourceManager<ShaderVK> shaders;
    ResourceManager<PipelineLayoutVK> pipelineLayouts;
    ResourceManager<RenderPipelineVK> renderPipelines;

    WindowVK window;
    DeviceVK device;
    
    RendererVK renderer;
};

}
