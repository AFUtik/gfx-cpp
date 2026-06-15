#pragma once

#include "Handle.hpp"

#include "BindGroupLayout.hpp"
#include <vector>

namespace gfx
{

struct PipelineLayout
{

}; 

struct PipelineLayoutDesc
{
    std::vector<Handle<BindGroupLayout>> layouts;
};

}