#pragma once

#include "gfx/RenderPass.hpp"

namespace gfx::gl
{

struct RenderPassGL : public RenderPass
{
    RenderPassGL(const RenderPassDesc& desc);
    ~RenderPassGL();

    int checkCompatibilityWithFBO(Handle<Framebuffer>& framebuffer) override;

    void setRenderPipeline(RenderPipeline* pipeline) override;
    void setBindGroup     (BindGroup* group) override;

    void begin(const Framebuffer* framebuffer) override;
    void end()   override;
private:
    RenderPipeline* currentPipeline = nullptr;
};

}