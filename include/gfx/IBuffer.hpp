#pragma once

#include "pch.hpp"

namespace gfx 
{

enum class BufferType
{
    Vertex,
    Index,
    Uniform,
    Storage,
    Staging
};

enum class BufferUsage
{
    Static,
    Dynamic,
    Stream
};

enum class BufferAccess
{
    GPUOnly,
    CPUToGPU,
    GPUToCPU
};

class Buffer
{
public:
    virtual ~Buffer() = default;

    virtual void write(const void* data, uint64_t size, uint64_t offset = 0) = 0;
    virtual void* map()  = 0;
    virtual void unmap() = 0;

    virtual uint64_t getSize() const = 0;
};

struct BufferDesc
{
    BufferType   type;
    BufferUsage  usage;
    BufferAccess access;
    uint64_t     size;
    bool cpuVisible = false;
};

}