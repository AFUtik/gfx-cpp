#pragma once

#include "IBuffer.hpp"
#include "GLTypes.hpp"

namespace gfx::gl
{

struct BufferGL : Buffer
{
    BufferGL(const Buffer&) = delete;
    BufferGL& operator=(const Buffer&) = delete;

    void writeToBuffer     (glt::data data, glt::size size, glt::size offset = 0) override;
    glt::size getBufferSize() const override;
private:
    glt::Buffer buffer;
    glt::size   size; // In bytes
};

}