#pragma once

#include "gfx/backend/vulkan/BindGroupLayout.hpp"
#include "gfx/backend/vulkan/Descriptors.hpp"
#include "gfx/backend/vulkan/Convert.hpp"
#include "gfx/backend/vulkan/Device.hpp"

namespace gfx::vk 
{

BindGroupLayoutVK::BindGroupLayoutVK(DeviceVK& device, const BindGroupLayoutDesc& desc)
{
    DescriptorSetLayout::Builder builder(device);
    for(const BindGroupLayoutEntry& entry : desc.entries)
    {
        VkDescriptorType descriptorType;
        if(std::holds_alternative<BufferTypeStruct>(entry.type))
        {
            BufferTypeStruct type = std::get<BufferTypeStruct>(entry.type);
            switch (type.type)
            {
                case BufferType::Uniform: {descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; break;}
                case BufferType::Storage: {descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER; break;}
                default: {}
            }
        }
        else if(std::holds_alternative<TextureTypeStruct>(entry.type))
        {
            TextureTypeStruct type = std::get<TextureTypeStruct>(entry.type);
            descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        }

        builder.addBinding(entry.binding, descriptorType, vk_convert::ToVk(entry.visibility));
    }
    descriptorSetLayout = builder.build();
}

}
