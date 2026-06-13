#pragma once

namespace gfx 
{

struct Pipeline
{
    virtual void bind() = 0;

    virtual ~Pipeline() = default;
};

}