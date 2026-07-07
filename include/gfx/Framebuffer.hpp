#pragma once

#include "Handle.hpp"
#include "ColorTarget.hpp"

#include "pch.hpp"

namespace gfx
{

struct Frame;
struct RenderPass;

struct Framebuffer
{
    virtual Image& getImage(Frame& frame, uint32_t attachment) = 0;
    virtual Image& getDepthImage(Frame& frame)                 = 0;
};

struct FramebufferDesc
{
    std::vector<ColorTargetDesc> colorDescs;
    ImageDesc depthDesc;

    Handle<RenderPass> renderPass;
};

}
