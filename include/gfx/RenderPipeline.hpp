#pragma once

#include "PipelineState.hpp"
#include "gfx/Vertex.hpp"

namespace gfx 
{

struct ColorTarget;
struct PipelineLayout;

struct CommandBuffer_T;
using CommandBuffer = CommandBuffer_T*; 

struct VertexState
{
    Handle<Shader> module;
    VertexLayout   layout;
};

struct FragmentState
{
    Handle<Shader> module;
};

struct RenderPipelineDesc
{
    VertexState   vertexState;
    FragmentState fragState;
    PipelineState  pipelineState;

    Handle<PipelineLayout> pipelineLayout;
};

struct RenderPipeline
{
    RenderPipelineDesc descriptor;

    virtual void bind(CommandBuffer) = 0;
};

}
