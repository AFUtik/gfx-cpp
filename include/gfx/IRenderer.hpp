#pragma once

namespace gfx 
{

struct Renderer
{
    virtual void beginFrame() = 0;
    virtual void endFrame()   = 0;

    virtual ~Renderer() = default;
};

}