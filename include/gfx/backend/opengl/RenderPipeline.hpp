#pragma once

#include "gfx/RenderPipeline.hpp"

namespace gfx::gl 
{

struct ColorTargetGL;

struct RenderPipelineGL : RenderPipeline
{
    RenderPipelineGL(const RenderPipelineDesc& desc);
    ~RenderPipelineGL();
private:
    uint32_t program;
};

}