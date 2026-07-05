#pragma once

#include "gfx/IDevice.hpp"

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

struct BackendVK : public gfx::Device
{
    BackendVK(Window* windowInstance);
    ~BackendVK();

    Handle<Image>          createImage (const ImageDesc& desc)  override {return {};};
    Handle<Buffer>         createBuffer(const BufferDesc& desc) override {return {};};

    Handle<MeshDesc>       meshDescHandle(const MeshDesc& desc) override {return {};};
    Handle<Mesh>           createMesh    (Handle<MeshDesc>& desc) override{return {};};

    Handle<Shader>         createShader(const ShaderDesc& desc) override{return {};};

    Handle<BindGroupLayout> createBindGroupLayout(const BindGroupLayoutDesc& desc) override{return {};};

    Handle<Framebuffer>    createFramebuffer     (const FramebufferDesc& desc) override{return {};};
    Handle<RenderPass>     createRenderPass      (const RenderPassDesc& desc)  override{return {};};
    Handle<PipelineState>  createPipelineState   ()  override{return {};};
    Handle<PipelineLayout> createPipelineLayout  (const PipelineLayoutDesc& desc) override{return {};};
    Handle<RenderPipeline> createRenderPipeline  (const RenderPipelineDesc& desc) override{return {};};

    Framebuffer*    getScreenFramebuffer() override
    {
        return nullptr;
    }

    WindowVK window;
    DeviceVK device;
    
    RendererVK renderer;
};

}
