#pragma once

#include <cstdint>

namespace gfx 
{

struct Buffer
{
    virtual void writeToBuffer(const void* data, uint64_t size, uint64_t offset) = 0;
    virtual uint64_t getBufferSize() const = 0;

    virtual ~Buffer() = default;
};

}