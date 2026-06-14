#pragma once

#include "gfx/Handle.hpp"
#include "gfx/IMesh.hpp"
#include "gfx/Vertex.hpp"

namespace gfx 
{
    struct MeshDesc;
}

namespace gfx::gl 
{

struct BackendGL;
struct BufferGL;

struct MeshDescGL : public MeshDesc
{
    MeshDescGL(const MeshDesc& desc);

    uint64_t glIndexType = 0x1405; // GL_UNSIGNED_INT
};

struct MeshGL : Mesh
{
    MeshGL(BackendGL& device, const Handle<MeshDescGL>& desc);
    ~MeshGL();

    void draw() override; 
    void draw(uint32_t instanceCount, uint32_t baseInstanceOffset = 0) override;

    void updateVertices(const void* data, uint64_t count) override;
    void updateIndexes (const void* data, uint64_t count) override;

    Buffer* getVertexBuffer()   override;
    Buffer* getIndexBuffer()    override;
    Buffer* getInstanceBuffer() override;
private:
    BackendGL&         device;
    Handle<MeshDescGL> descriptor;

    uint32_t vao       = 0;
    Handle<Buffer> vbo = {};
    Handle<Buffer> ebo = {};

    uint32_t vertexCount = 0;
    uint32_t indexCount  = 0;
};

}