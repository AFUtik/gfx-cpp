#pragma once

#include "gfx/IShader.hpp"

namespace gfx::gl
{

struct ShaderGL : Shader
{
    ShaderGL(const ShaderDesc& desc);
    ~ShaderGL();
private:
    uint32_t shader;

    friend class RenderPipelineGL;
};

}