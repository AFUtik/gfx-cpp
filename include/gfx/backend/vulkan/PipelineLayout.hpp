#pragma once

#include "gfx/PipelineLayout.hpp"

struct VkPipelineLayout_T;
using VkPipelineLayout = VkPipelineLayout_T*;

namespace gfx::vk 
{

struct DeviceVK;

struct PipelineLayoutVK : public PipelineLayout
{
    PipelineLayoutVK(DeviceVK& device, const PipelineLayoutDesc& desc);
    ~PipelineLayoutVK();

    VkPipelineLayout getPipelineLayout() {return pipelineLayout;}
private:
    DeviceVK& device;
    VkPipelineLayout pipelineLayout;
};

}
