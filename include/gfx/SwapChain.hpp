#pragma once

#include "gfx/Framebuffer.hpp"

namespace gfx
{

enum class PresentMode 
{
    Immediate,
    FIFO,
    Mailbox
};

struct SwapchainDesc
{
    FramebufferDesc framebufferDesc;
    PresentMode     mode;
};

}
