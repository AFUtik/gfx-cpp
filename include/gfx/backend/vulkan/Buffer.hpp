#pragma once

#include "gfx/IBuffer.hpp"

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

namespace gfx::vk {

struct DeviceVK;

class BufferVK : public Buffer {
public:
    BufferVK(
        DeviceVK &device,
        VkDeviceSize instanceSize,
        uint32_t instanceCount,
        VkBufferUsageFlags usageFlags,
        VkMemoryPropertyFlags memoryPropertyFlags,
        VmaMemoryUsage memoryUsage,
        VkDeviceSize minOffsetAlignment = 1);
    ~BufferVK();

    BufferVK(const BufferVK&) = delete;
    BufferVK& operator=(const BufferVK&) = delete;

    virtual void write(const void* data, uint64_t size, uint64_t offset = 0) override;
    virtual void* map()  override;
    virtual void unmap() override;
    virtual uint64_t getSize() const override {return bufferSize;}; 

    VkResult flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
    VkDescriptorBufferInfo descriptorInfo(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
    VkResult invalidate(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

    void writeToIndex(void* data, int index);
    VkResult flushIndex(int index);
    VkDescriptorBufferInfo descriptorInfoForIndex(int index);
    VkResult invalidateIndex(int index);

    VkBuffer getBuffer() const { return buffer; }
    void* getMappedMemory() const { return mapped; }
    uint32_t getInstanceCount() const { return instanceCount; }
    VkDeviceSize getInstanceSize() const { return instanceSize; }
    VkDeviceSize getAlignmentSize() const { return instanceSize; }
    VkBufferUsageFlags getUsageFlags() const { return usageFlags; }
    VkMemoryPropertyFlags getMemoryPropertyFlags() const { return memoryPropertyFlags; }

    #ifndef NDEBUG
    void addDebugInfo(const char* info);
    #endif
private:
    static VkDeviceSize getAlignment(VkDeviceSize instanceSize, VkDeviceSize minOffsetAlignment);

    DeviceVK& device;
    void* mapped = nullptr;
    VkBuffer buffer = VK_NULL_HANDLE;
    VmaAllocation vmaAllocation;

    VkDeviceSize bufferSize;
    uint32_t instanceCount;
    VkDeviceSize instanceSize;
    VkDeviceSize alignmentSize;
    VkBufferUsageFlags usageFlags;
    VkMemoryPropertyFlags memoryPropertyFlags;

    friend class DeviceVK;
};

}  // namespace myvk
