#pragma once

#include "IDevice.hpp"
#include <cstdint>

namespace gfx 
{

struct Buffer;
struct VertexLayout;

struct Mesh
{
    virtual void draw() = 0;
    
    virtual void updateVertices(const void* data, uint64_t count) = 0;

    virtual Buffer* getVertexBuffer()   = 0;
    virtual Buffer* getIndexBuffer()    = 0;
    virtual Buffer* getInstanceBuffer() = 0;

    virtual ~Mesh() = default;
};

struct MeshDesc
{
    VertexLayout& layout;
};

}