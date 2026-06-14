#pragma once

#include "Handle.hpp"

#include <cstdint>
#include <vector>

namespace gfx 
{

enum BindingType
{
    Buffer,
    Image
};

enum BufferBindingType
{
    Uniform,
    SSBO
};

struct BindGroupLayout;

struct BindGroupEntry
{
    uint32_t             binding  = 0;
    Handle<unknown_type> resource = {};
};

struct BindGroup 
{
    Handle<BindGroupLayout>     layout;
    std::vector<BindGroupEntry> entries;
};

}