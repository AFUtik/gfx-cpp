#pragma once

#include "Handle.hpp"
#include "BindGroupLayout.hpp"

#include "pch.hpp"

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