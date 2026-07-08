#pragma once

#include "gfx/backend/vulkan/BindGroup.hpp"
#include "gfx/backend/vulkan/BindGroupLayout.hpp"
#include "gfx/backend/vulkan/Device.hpp"

#include "gfx/backend/vulkan/Buffer.hpp"
#include "gfx/backend/vulkan/Image.hpp"

namespace gfx::vk 
{

    
BindGroupVK::BindGroupVK(
    DeviceVK& device,
    BindGroupLayoutVK& bindGroupLayout,
    DescriptorPoolManager& descriptorPoolManager) : 

    writer(bindGroupLayout.getDescriptorSetLayout(), descriptorPoolManager), 
    descriptorSet(VK_NULL_HANDLE),
    set(bindGroupLayout.getSet())
{}
 
void BindGroupVK::setBuffer(uint32_t binding, Handle<Buffer>& buffer)
{
    BufferVK* bufferVK = reinterpret_cast<BufferVK*>(buffer.Get());
    VkDescriptorBufferInfo bufferInfo {
        .buffer = bufferVK->getBuffer(),
        .offset = 0,
        .range  = bufferVK->getSize()
    };
    writer.writeBuffer(binding, &bufferInfo);
    write();
}

void BindGroupVK::setImage (uint32_t binding, Handle<Image>& image)
{
    ImageVK* imageVK = reinterpret_cast<ImageVK*>(image.Get());
    VkDescriptorImageInfo imageInfo {
        .sampler     = imageVK->getSampler(), 
        .imageView   = imageVK->getView(),
        .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    };
    writer.writeImage(binding, &imageInfo);
    write();
}

void BindGroupVK::write()
{
    if(descriptorSet==VK_NULL_HANDLE) 
    {
       writer.build(descriptorSet);
    }
    else 
    {
        // writer.overwrite(descriptorSet);
    }
    writer.clear();
}

}
