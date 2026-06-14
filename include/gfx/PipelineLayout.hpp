#pragma once

#include "BindGroupLayout.hpp"
#include <vector>

namespace gfx
{

struct PipelineLayout
{

}; 

struct PipelineLayoutDesc
{
    std::vector<BindGroupLayout> layouts;

    inline PipelineLayoutDesc& add(const BindGroupLayout& group)
    {
        layouts.push_back(group);
        return *this;
    }
};

}