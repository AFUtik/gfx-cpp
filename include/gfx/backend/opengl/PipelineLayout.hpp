#pragma once

#include "gfx/PipelineLayout.hpp"

namespace gfx::gl 
{

struct PipelineLayoutGL : PipelineLayout
{
    PipelineLayoutGL(const PipelineLayoutDesc& desc) {}
    ~PipelineLayoutGL() {}
};

}