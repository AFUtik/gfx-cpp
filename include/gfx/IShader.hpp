#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "Handle.hpp"

namespace gfx 
{

enum class ShaderStage
{
    Vertex,
    Fragment,
    Geometry,
    TessControl,
    TessEvaluation,
    Compute,
    RTX
};

struct Shader
{

};

struct ShaderDesc
{
    ShaderStage stage;
    std::string openglShader = "";
    std::string vulkanShader = "";

    virtual Handle<Shader> compile() = 0;
};


struct ResourceSlot
{
    enum class Type
    {
        Texture,
        UniformBuffer,
        StorageBuffer
    };

    uint32_t set;
    uint32_t binding;

    Type type;
    ShaderStage stages;
};

struct ShaderResourceSignature
{
    std::vector<ResourceSlot> sets;
};

}