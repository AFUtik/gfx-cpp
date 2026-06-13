#pragma once

#include "gfx/IShader.hpp"

namespace gfx::gl
{

struct ShaderDescGL;

struct ShaderGL : Shader
{
private:
    uint32_t             shader;
    Handle<ShaderDescGL> descriptor;
};

struct ShaderDescGL : ShaderDesc
{
    Handle<Shader> compile() override;
};


}