#pragma once

#include "Handle.hpp"

namespace gfx 
{

struct Pipeline;
struct Renderer;

struct RenderPass
{
    Handle<Pipeline>& pipeline;
    Renderer*         renderer = nullptr;
};

}