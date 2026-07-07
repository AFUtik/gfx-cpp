#pragma once

#include "gfx/Framebuffer.hpp"
#include "gfx/IImage.hpp"

namespace gfx
{

struct Frame;

enum class PresentMode 
{
    Immediate,
    FIFO,
    Mailbox
};

struct SwapchainDesc
{
    PresentMode mode = PresentMode::FIFO;

    bool        createDepth = true;
};

struct Swapchain
{
    virtual Image& getImage(Frame& frame)      = 0;
    virtual Image& getDepthImage(Frame& frame) = 0;
};

}
