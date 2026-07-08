#pragma once

#include "gfx/BindGroupLayout.hpp"

#include "pch.hpp"

namespace gfx::vk 
{

struct DeviceVK;
struct DescriptorSetLayout;

struct BindGroupLayoutVK : public BindGroupLayout
{
    BindGroupLayoutVK(DeviceVK& device, const BindGroupLayoutDesc& desc);
    ~BindGroupLayoutVK() = default;

    DescriptorSetLayout& getDescriptorSetLayout() {return *descriptorSetLayout.get();}
    uint32_t getSet() {return set;}
private:
    std::unique_ptr<DescriptorSetLayout> descriptorSetLayout;
    uint32_t set = 0;
};

}
