#pragma once

#include "gfx/BindGroupLayout.hpp"

namespace gfx::gl
{

struct BindGroupLayoutGL : BindGroupLayout
{
    BindGroupLayoutGL(const BindGroupLayoutDesc& desc);

    std::vector<BindGroupLayoutEntry> layoutEntries;
};

}