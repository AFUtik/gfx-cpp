#pragma once

namespace gfx
{

struct CommandBuffer {};

struct Frame
{
    CommandBuffer* cmdBuf = nullptr;
    int imageIndex        = 0;
};

}
