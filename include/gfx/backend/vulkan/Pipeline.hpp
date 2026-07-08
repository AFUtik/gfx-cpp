#pragma once

#include "gfx/RenderPipeline.hpp"

struct VkPipeline_T;
using VkPipeline = VkPipeline_T*;

struct VkPipelineLayout_T;
using VkPipelineLayout = VkPipelineLayout_T*;

namespace gfx::vk 
{

struct DeviceVK;

struct RenderPipelineVK : public RenderPipeline 
{
    RenderPipelineVK(DeviceVK& device, const RenderPipelineDesc& desc);
    ~RenderPipelineVK();

    void bind(CommandBuffer cmdBuf) override;
    void bindGroup(CommandBuffer, Handle<BindGroup>& bindGroup) override;
private:
    DeviceVK& device;

    VkPipeline graphicsPipeline;
    VkPipelineLayout pipelineLayout;
}; 

}
