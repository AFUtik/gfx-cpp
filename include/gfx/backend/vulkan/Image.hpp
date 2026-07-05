#pragma once

#include "gfx/IImage.hpp"
#include <vulkan/vulkan.h>

struct VmaAllocation_T;
using VmaAllocation = VmaAllocation_T*;

namespace gfx::vk {
    struct DeviceVK;

    struct ImageVK : Image {
        public:
            ImageVK(DeviceVK& device, const ImageDesc& desc);
            ~ImageVK();

            ImageVK(const ImageVK&) = delete;
            ImageVK& operator=(const ImageVK&) = delete;

            ImageVK(ImageVK&&) noexcept;
            ImageVK& operator=(ImageVK&&) noexcept;

            VkSampler   getSampler() {return sampler;}
            VkImageView getView() {return view;}

#ifndef NDEBUG
            void addDebugInfo(const char* info);
#endif

            void write(const uint8_t* pixels) override;
            void setImageFilter(gfx::ImageFilter filter) override;
            void bind() override {};
        private:
            DeviceVK& device;

            void createTextureSampler(
                    VkSampler& sampler, 
                    VkFilter MinFilter, 
                    VkFilter MaxFilter, 
                    VkSamplerAddressMode AddressMode);

            void updateTextureImage(int layerCount, const void* pPixels);

            void createImageView(VkImageAspectFlags AspectFlags);

            void createImage();

            void createTexture(const uint8_t* pixels, uint32_t channels, gfx::ImageFilter filter);

            bool isCubemap = false;

            VmaAllocation vmaAllocation  = VK_NULL_HANDLE;
            VkImage       image          = VK_NULL_HANDLE;
            VkImageView   view           = VK_NULL_HANDLE;
            VkSampler     sampler        = VK_NULL_HANDLE;
            VkImageLayout imageLayout = VK_IMAGE_LAYOUT_UNDEFINED;

            uint32_t imageWidth, imageHeight, channels;
            VkFormat format;

            friend struct DeviceVK;
    };

}
