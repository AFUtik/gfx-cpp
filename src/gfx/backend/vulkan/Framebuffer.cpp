#include "gfx/backend/vulkan/Framebuffer.hpp"
#include "gfx/backend/vulkan/Renderer.hpp"
#include "gfx/backend/vulkan/Device.hpp"

#include "gfx/Frame.hpp"

namespace gfx::vk 
{

FramebufferVK::FramebufferVK(
        DeviceVK& device, 
        Frame& frame, 
        int bufferCount,
        FramebufferDesc& desc) : device(device), frame(frame)
{
    images.resize(bufferCount);
    for (auto& imageArray : images)
    {
        imageArray.reserve(desc.colorDescs.size());
        for (const auto& colorDesc : desc.colorDescs) imageArray.emplace_back(device, colorDesc.imageDesc);
    }

    depthImages .reserve(bufferCount);
    for (int i = 0; i < bufferCount; i++) depthImages.emplace_back(device, desc.depthDesc);
    framebuffers.resize(bufferCount);

    createFramebuffers();
}

Image& FramebufferVK::getImage(uint32_t attachment)
{
    return images[frame.imageIndex][attachment];
}

Image& FramebufferVK::getDepthImage()
{
    return depthImages[frame.imageIndex];
}

void FramebufferVK::createFramebuffers()
{
     
}

}
