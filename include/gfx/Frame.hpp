#pragma once

namespace gfx
{

struct CommandBuffer_T {};
using CommandBuffer = CommandBuffer_T*;

struct Frame
{
    CommandBuffer cmdBuf = nullptr;
    int imageIndex       = 0;
};

}
