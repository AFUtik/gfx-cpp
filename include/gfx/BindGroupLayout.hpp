#pragma once

#include "gfx/IShader.hpp"
#include "gfx/IBuffer.hpp"

#include "pch.hpp"

namespace gfx 
{
 
enum TextureSampleType {
    Float,
    Depth,
    Sint,
    Uint,
};

struct BufferTypeStruct
{
    BufferType type;
};

struct TextureTypeStruct
{
    TextureSampleType sample_type;
};

using BindingType = std::variant<
    BufferTypeStruct,
    TextureTypeStruct
>;

enum BindingTypeEnum
{
    BINDING_TYPE_BUFFER,
    BINDING_TYPE_IMAGE,
};

struct BindGroupLayoutEntry
{
    BindingType type;
    ShaderStage visibility;
    uint32_t    binding = 0;
    
    // For GLSL shader
    std::string uniformName = ""; 
};

struct BindGroupLayoutDesc
{
    std::vector<BindGroupLayoutEntry> entries;
    uint32_t set =0;

    inline BindGroupLayoutDesc& add(const BindGroupLayoutEntry& entry)
    {
        entries.push_back(entry);
        return *this;
    }
};

struct BindGroupLayout {};

}
