#pragma once

#include "gfx/IImage.hpp"
#include <vulkan/vulkan.h>

struct VmaAllocation_T;
using VmaAllocation = VmaAllocation_T*;

namespace gfx::vk {
    struct DeviceVK;

    struct SamplerVK : public Sampler 
    {
        SamplerVK(DeviceVK& device, const SamplerDesc& desc);
        ~SamplerVK();
    private:
        DeviceVK& device;

        void createTextureSampler(
                VkSampler& sampler, 
                VkFilter MinFilter, 
                VkFilter MaxFilter, 
                VkSamplerAddressMode AddressMode);

        VkSampler sampler;
    };

    struct ImageVK : public Image 
    {
        public:
            ImageVK(DeviceVK& device, 
                    VkImage     vkImage, 
                    VkImageView vkImageView);

            ImageVK(DeviceVK& device, const ImageDesc& desc);
            ~ImageVK();

            ImageVK(const ImageVK&) = delete;
            ImageVK& operator=(const ImageVK&) = delete;

            ImageVK(ImageVK&& other) = default;

            VkImageView getView() {return view;}
#ifndef NDEBUG
            void addDebugInfo(const char* info);
#endif
            void write(const uint8_t* pixels) override;
            void bind() override {};
        private:
            DeviceVK& device;


            void updateTextureImage(int layerCount, const void* pPixels);
            void createImageView(VkImageAspectFlags AspectFlags);
            void createImage();
            void createTexture(const uint8_t* pixels, uint32_t channels, gfx::ImageFilter filter);

            bool isCubemap  = false;

            VmaAllocation vmaAllocation  = VK_NULL_HANDLE;
            VkImage       image          = VK_NULL_HANDLE;
            VkImageView   view           = VK_NULL_HANDLE;
            VkImageLayout imageLayout    = VK_IMAGE_LAYOUT_UNDEFINED;

            uint32_t imageWidth = 0, imageHeight = 0;
            VkFormat format;

            friend struct DeviceVK;
    };

}
