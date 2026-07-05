#pragma once

#include "Frame.hpp"

namespace gfx 
{

struct Renderer
{
    virtual Frame& beginFrame() = 0;
    virtual void   endFrame()   = 0;

    virtual ~Renderer() = default;
};

}
