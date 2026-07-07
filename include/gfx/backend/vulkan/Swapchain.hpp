#pragma once

#include "Image.hpp"

#include "gfx/SwapChain.hpp"
#include <vulkan/vulkan.h> 

#include "pch.hpp"

struct VmaAllocation_T;
using VmaAllocation = VmaAllocation_T*;

namespace gfx::vk {
    struct DeviceVK;

    struct SwapChain : public Swapchain
    {
        static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

        SwapChain(DeviceVK& device, VkExtent2D windowExtent, PresentMode mode);
        SwapChain(DeviceVK& device, VkExtent2D windowExtent, PresentMode mode, std::shared_ptr<SwapChain> previous);
        ~SwapChain();

        void init();

        SwapChain(const SwapChain&) = delete;
        SwapChain& operator=(const SwapChain&) = delete;

        VkFramebuffer getFrameBuffer(int index) { return swapChainFramebuffers[index]; }
        VkRenderPass getRenderPass() { return renderPass; }
        size_t imageCount() { return swapChainImages.size(); }
        VkFormat getSwapChainImageFormat() { return swapChainImageFormat; }
        VkExtent2D getSwapChainExtent() { return swapChainExtent; }
        uint32_t width() { return swapChainExtent.width; }
        uint32_t height() { return swapChainExtent.height; }

        float extentAspectRatio() {
            return static_cast<float>(swapChainExtent.width) / static_cast<float>(swapChainExtent.height);
        }
        VkFormat findDepthFormat();

        VkResult acquireNextImage(uint32_t* imageIndex);
        VkResult submitCommandBuffers(const VkCommandBuffer* buffers, uint32_t* imageIndex);

        bool compareSwapFormats(const SwapChain& swapchain) const {
            return swapchain.swapChainDepthFormat == swapChainDepthFormat
                && swapchain.swapChainImageFormat == swapChainImageFormat;
        }

        VkImageView getImageView(int index) { return swapChainImageViews[index]; }
        VkImageView getDepthImageView(int index) { return depthImageViews[index]; }
        VkImage     getImage(int index) {return swapChainImages[index];  }
        VkImage     getDepthImage(int index) {return depthImages[index]; }
 
        Image& getImage     (Frame& frame) override;
        Image& getDepthImage(Frame& frame) override;
    private:
        void createSwapChain();
        void createImageViews();
        void createDepthResources();
        void createRenderPass();
        void createFramebuffers();
        void createSyncObjects();

        // Helper functions
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(
            const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(
            const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

        VkFormat swapChainImageFormat;
        VkFormat swapChainDepthFormat;
        VkExtent2D swapChainExtent;

        std::vector<VkFramebuffer> swapChainFramebuffers;
        VkRenderPass renderPass;

        std::vector<VkImage>       depthImages;
        std::vector<VkImageView>   depthImageViews;
        std::vector<VmaAllocation> depthImageAllocs;
        std::vector<ImageVK>       depthImagesVK;

        std::vector<VkImage>     swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<ImageVK>     swapChainImagesVK;

        std::shared_ptr<SwapChain> oldSwapChain;

        PresentMode presentMode;
        VkExtent2D windowExtent;

        VkSwapchainKHR swapChain;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        size_t currentFrame = 0;
        
        DeviceVK& device;
    };
}
