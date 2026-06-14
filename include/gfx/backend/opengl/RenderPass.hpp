#pragma once

#include "gfx/RenderPass.hpp"

namespace gfx::gl
{

struct RenderPassGL : public RenderPass
{
    RenderPassGL(const RenderPassDesc& desc);
    ~RenderPassGL();

    void begin() override;
    void end()   override;
protected:
    RenderPassGL();
protected:
    void createFBO(const RenderPassDesc& desc);

    uint32_t fbo;
    uint32_t fbo_width  = 0 ;
    uint32_t fbo_height = 0;
};

struct ScreenRenderPassGL : public RenderPassGL
{
    ScreenRenderPassGL(const RenderPassDesc& desc);
};

}