#pragma once

#include "pch.hpp"

namespace gfx 
{

enum class ShaderStage
{
    Vertex          = 1<<0,
    Fragment        = 1<<1,
    Geometry        = 1<<2,
    TessControl     = 1<<3,
    TessEvaluation  = 1<<4,
    Compute         = 1<<5
};

struct Shader
{
    virtual ~Shader() = default;
};

struct ShaderDesc
{
    std::string name;
    const uint32_t* spirv      = nullptr;
    uint64_t        spirv_size = 0;
    const char*     glsl       = nullptr;
    ShaderStage stage;
};

}
