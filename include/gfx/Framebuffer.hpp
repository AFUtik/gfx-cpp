#pragma once

#include "ColorTarget.hpp"
#include "pch.hpp"

namespace gfx
{

struct Framebuffer
{
    virtual Image& getImage(uint32_t attachment) = 0;
    virtual Image& getDepthImage()               = 0;
};

struct FramebufferDesc
{
    std::vector<ColorTargetDesc> colorDescs;
    ImageDesc depthDesc;
};

}
