#pragma once

#include "PipelineDesc.hpp"
#include "IPipeline.hpp"

namespace gfx::gl 
{

struct PipelineDescGL;

struct PipelineGL : Pipeline
{
private:
    uint32_t               program;
    Handle<PipelineDescGL> descriptor;
};

struct PipelineDescGL : PipelineDesc
{
    Handle<Pipeline> build() override = 0;
};

}