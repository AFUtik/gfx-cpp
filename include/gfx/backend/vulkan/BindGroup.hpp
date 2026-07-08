#pragma once

#include "gfx/BindGroup.hpp"
#include "Descriptors.hpp"

#include "pch.hpp"

namespace gfx::vk 
{

struct DeviceVK;
struct BindGroupLayoutVK;

struct BindGroupVK : public BindGroup
{
    BindGroupVK(
            DeviceVK& device,
            BindGroupLayoutVK& bindGroupLayout,
            DescriptorPoolManager& descriptorPoolManager);
    ~BindGroupVK() = default;
 
    void setBuffer(uint32_t binding, Handle<Buffer>& buffer) override;
    void setImage (uint32_t binding, Handle<Image>& image)   override;
    void write() override;

    VkDescriptorSet getDescriptorSet() { return descriptorSet; }
    uint32_t getSet() {return set;}
private:
    DescriptorWriter writer;
    VkDescriptorSet  descriptorSet;
    uint32_t set = 0;
};

}
