#pragma once

#include "PipelineState.hpp"

#include "gfx/Vertex.hpp"

namespace gfx 
{

struct ColorTarget;
struct PipelineLayout;

struct VertexState
{
    Handle<Shader> module;
    VertexLayout   layout;
};

struct FragmentState
{
    Handle<Shader> module;
    std::vector<Handle<ColorTarget>> targets;
};

struct RenderPipeline
{

};

struct RenderPipelineDescriptor
{
    VertexState   vertexState;
    FragmentState fragState;

    Handle<PipelineState>  pipelineState;
    Handle<PipelineLayout> pipelineLayout;
};

}