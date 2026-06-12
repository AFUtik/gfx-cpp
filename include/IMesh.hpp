#pragma once

#include <cstdint>

namespace gfx 
{

struct Buffer;

struct Mesh
{
    virtual void updateVertexBuffer   (const void* vertices, uint64_t size)  = 0;
    virtual void updateIndexBuffer    (const void* indices, uint64_t size)   = 0;
    virtual void updateInstanceBuffer (const void* instances, uint64_t size) = 0;

    virtual const Buffer* getVertexBuffer() const   = 0;
    virtual const Buffer* getIndexBuffer() const    = 0;
    virtual const Buffer* getInstanceBuffer() const = 0;

    virtual ~Mesh() = default;
};

}