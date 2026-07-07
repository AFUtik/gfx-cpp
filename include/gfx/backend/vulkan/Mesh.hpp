#pragma once

#include "gfx/IMesh.hpp"
#include "gfx/Handle.hpp"

namespace gfx::vk 
{

struct DeviceVK;
struct BufferVK;

struct MeshVK : public Mesh
{
    MeshVK(DeviceVK& device, const MeshDesc& desc);
    ~MeshVK();

    void draw(CommandBuffer) override;
    void draw(uint32_t instanceCount, uint32_t instanceOffset) override {};
    
    void updateVertices(const void* data, uint64_t count) override;
    void updateIndexes (const void* data, uint64_t count) override;

    Buffer* getVertexBuffer()   override;
    Buffer* getIndexBuffer()    override;
    Buffer* getInstanceBuffer() override;
private:
    void createVertexBuffer(uint64_t size);
    void createIndexBuffer (uint64_t size);

    DeviceVK& device;

    std::unique_ptr<BufferVK> vertexBuffer;
    std::unique_ptr<BufferVK> indexBuffer;
    std::unique_ptr<BufferVK> instanceBuffer;
    BufferUsage bufferUsage;

    uint32_t vkIndexType;

    uint32_t vertexCount   = 0;
	uint32_t indexCount    = 0;
	uint32_t instanceCount = 1;

	uint8_t vertexStride   = 0;
	uint8_t indexStride    = 0;
	uint8_t instanceStride = 0;
};

}
