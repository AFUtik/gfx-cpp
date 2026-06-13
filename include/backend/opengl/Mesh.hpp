#pragma once

#include "Handle.hpp"
#include "IMesh.hpp"
#include "Vertex.hpp"

namespace gfx 
{
    struct MeshDesc;
}

namespace gfx::gl 
{

struct BackendGL;
struct BufferGL;

struct MeshGL : Mesh
{
    MeshGL(BackendGL& device, const MeshDesc& desc);
    ~MeshGL();

    void draw() override; 

    void updateVertices(const void* data, uint64_t count) override;

    Buffer* getVertexBuffer()   override;
    Buffer* getIndexBuffer()    override;
    Buffer* getInstanceBuffer() override;
private:
    BackendGL&    device;
    VertexLayout& layout;

    uint32_t vao       = 0;
    Handle<Buffer> vbo = {};

    uint32_t vertexCount = 0;
};

}