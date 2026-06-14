#pragma once

#include <cstdint>
#include <vector>
#include <variant>

namespace gfx 
{

enum BufferBindingType
{
    Uniform,
    SSBO
};

enum TextureSampleType {
    Float,
    Depth,
    Sint,
    Uint,
};

struct BufferTypeStruct
{
    BufferBindingType type;
};

struct TextureTypeStruct
{
    TextureSampleType sample_type;
};

using BindingType = std::variant<
    BufferTypeStruct,
    TextureTypeStruct
>;

struct BindGroupLayoutEntry
{
    BindingType type;
    uint32_t binding = 0;
    uint32_t visibility;
};

struct BindGroupLayout
{
    std::vector<BindGroupLayoutEntry> entries;

    inline BindGroupLayout& add(const BindGroupLayoutEntry& entry)
    {
        entries.push_back(entry);
        return *this;
    }
};

}