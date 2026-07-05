#pragma once

#include "gfx/Framebuffer.hpp"
#include "gfx/backend/vulkan/Image.hpp"

#include "pch.hpp"

namespace gfx
{

struct Frame;

}

namespace gfx::vk 
{

struct DeviceVK;
struct SwapChain;

struct FramebufferVK : public Framebuffer 
{
    FramebufferVK(
            DeviceVK& device,
            Frame&    frame,
            int       bufferCount,
            FramebufferDesc& desc);

    ~FramebufferVK();

    Image& getImage(uint32_t attachment) override;
    Image& getDepthImage() override;
private:
    void createFramebuffers();

    DeviceVK& device;
    Frame&    frame;
    
    std::vector<std::vector<ImageVK>> images;
    std::vector<ImageVK>              depthImages;
    std::vector<VkFramebuffer>        framebuffers;
};

}
