#pragma once

#include <cstdint>
#include <vector>

namespace gfx 
{

struct BindGroupLayoutEntry
{
    uint32_t binding = 0;
    uint32_t visibility;
};

struct BindGroupLayout
{
    std::vector<BindGroupLayoutEntry> entries;
};

}