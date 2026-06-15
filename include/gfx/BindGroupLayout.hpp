#pragma once

#include <cstdint>
#include <vector>
#include <variant>
#include <string>

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
    uint32_t type;
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
    uint32_t binding     = 0;
    uint32_t visibility;
    
    // For GLSL shader
    std::string uniformName = ""; 
};

struct BindGroupLayoutDesc
{
    std::vector<BindGroupLayoutEntry> entries;

    inline BindGroupLayoutDesc& add(const BindGroupLayoutEntry& entry)
    {
        entries.push_back(entry);
        return *this;
    }
};

struct BindGroupLayout {};

}