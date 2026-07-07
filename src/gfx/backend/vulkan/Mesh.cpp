#include "gfx/backend/vulkan/Mesh.hpp"
#include "gfx/backend/vulkan/Device.hpp"
#include "gfx/backend/vulkan/Buffer.hpp"
#include "gfx/backend/vulkan/Convert.hpp"

static size_t nextPow2(size_t v) noexcept 
{
    if (v == 0) return 1;

    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;

    return v;
}


namespace gfx::vk 
{

MeshVK::MeshVK(DeviceVK& device, const MeshDesc& desc) : 
    device(device), 
    bufferUsage(desc.bufferUsage),
    vkIndexType(vk_convert::ToIndexTypeVk(desc.indexStride)),

    vertexStride(desc.layout.stride),
    indexStride (desc.indexStride)
{
    
}

MeshVK::~MeshVK()
{

}

void MeshVK::draw(CommandBuffer cmdBuf_)
{
    VkCommandBuffer commandBuffer = reinterpret_cast<VkCommandBuffer>(cmdBuf_); 
    VkBuffer buffers[] = { vertexBuffer->getBuffer() };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
    if (indexBuffer) vkCmdBindIndexBuffer(commandBuffer, indexBuffer->getBuffer(), 0, static_cast<VkIndexType>(vkIndexType));

    if (indexBuffer) {
        vkCmdDrawIndexed(commandBuffer, indexCount, instanceCount, 0, 0, 0);
    } else {
        vkCmdDraw(commandBuffer, vertexCount, instanceCount, 0, 0);
    }
}


void MeshVK::createVertexBuffer(uint64_t size)
{
    assert(size >= 3 && "Not enough vertices");

    VkDeviceSize bufferSize = static_cast<uint64_t>(vertexStride) * size;
    if(bufferUsage == BufferUsage::Static) {
        vertexBuffer = std::make_unique<BufferVK>(
                device,
                bufferSize,
                1,
                VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                0,
                VMA_MEMORY_USAGE_GPU_ONLY
                );
    } 
    else {
        vertexBuffer = std::make_unique<BufferVK>(
                device,
                bufferSize,
                1,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                0,
                VMA_MEMORY_USAGE_CPU_TO_GPU
                );
    }
}

void MeshVK::createIndexBuffer (uint64_t size)
{
    VkDeviceSize bufferSize = static_cast<uint64_t>(indexStride) * size;
    if(bufferUsage == BufferUsage::Static) {
        indexBuffer = std::make_unique<BufferVK>(
                device,
                bufferSize,
                1,
                VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                0,
                VMA_MEMORY_USAGE_GPU_ONLY
                );
    } 
    else {
        indexBuffer = std::make_unique<BufferVK>(
                device,
                bufferSize,
                1,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                0,
                VMA_MEMORY_USAGE_CPU_TO_GPU
                );
    }
}

void MeshVK::updateVertices(const void* data, uint64_t count)
{
    if(count==0) return;

    vertexCount = count;
    VkDeviceSize updateSize = static_cast<size_t>(vertexStride) * count;

    if(!vertexBuffer || updateSize > vertexBuffer->getSize())
        createVertexBuffer(nextPow2(count));

    if (bufferUsage == BufferUsage::Static)
    {
        BufferVK stagingBuffer(
                device,
                updateSize,
                1,
                VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                VMA_MEMORY_USAGE_CPU_ONLY
                );

        stagingBuffer.map();
        stagingBuffer.write(data, updateSize);
        stagingBuffer.unmap();

        device.copyBuffer(
                stagingBuffer.getBuffer(),
                vertexBuffer->getBuffer(),
                updateSize
                );
    }
    else
    {
        vertexBuffer->map();
        vertexBuffer->write(data, updateSize);
    }
}

void MeshVK::updateIndexes (const void* data, uint64_t count)
{
    if(count==0) return;

    indexCount = count;
    VkDeviceSize updateSize = static_cast<size_t>(indexStride) * count;
    if(!indexBuffer || updateSize > indexBuffer->getSize())
        createIndexBuffer(nextPow2(count));

    if (bufferUsage == BufferUsage::Static)
    {
        BufferVK stagingBuffer(
                device,
                updateSize,
                1,
                VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                VMA_MEMORY_USAGE_CPU_ONLY
                );

        stagingBuffer.map();
        stagingBuffer.write(data, updateSize);
        stagingBuffer.unmap();

        device.copyBuffer(
                stagingBuffer.getBuffer(),
                indexBuffer->getBuffer(),
                updateSize
                );
    }
    else
    {
        indexBuffer->map();
        indexBuffer->write(data, updateSize);
    }
}

Buffer* MeshVK::getVertexBuffer()   {return vertexBuffer.get();};
Buffer* MeshVK::getIndexBuffer()    {return indexBuffer.get();};
Buffer* MeshVK::getInstanceBuffer() {return instanceBuffer.get();};

}
