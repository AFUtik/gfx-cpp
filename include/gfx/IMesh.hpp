#pragma once

#include "IDevice.hpp"
#include <cstdint>

#include "Vertex.hpp"

namespace gfx 
{

struct Buffer;

struct Mesh
{
    virtual void draw() = 0;
    virtual void draw(uint32_t instanceCount, uint32_t instanceOffset) = 0;
    
    virtual void updateVertices(const void* data, uint64_t count) = 0;
    virtual void updateIndexes (const void* data, uint64_t count) = 0;

    virtual Buffer* getVertexBuffer()   = 0;
    virtual Buffer* getIndexBuffer()    = 0;
    virtual Buffer* getInstanceBuffer() = 0;

    virtual ~Mesh() = default;
};

struct MeshDesc
{
    VertexLayout layout;
    uint64_t     indexStride = 4;
};

}