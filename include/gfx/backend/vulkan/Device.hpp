#pragma once

#define VMA_DEBUG_INITIALIZE_ALLOCATIONS 1
#define VMA_STATS_STRING_ENABLED 1
#include <vk_mem_alloc.h>
#include <vulkan/vulkan.h>

#include "pch.hpp"

namespace gfx::vk {
    struct WindowVK;

    struct DeletionQueue
    {
        std::deque<std::function<void()>> deletors;

		DeletionQueue() = default;
		~DeletionQueue() {}

		DeletionQueue(const DeletionQueue&) = delete;
    	DeletionQueue& operator=(const DeletionQueue&) = delete;

		DeletionQueue(DeletionQueue&&) noexcept = default;
		DeletionQueue& operator=(DeletionQueue&&) noexcept = default;

        void push_function(std::function<void()>&& function) {
            deletors.push_back(function);
        }

        void flush() {
            if(!deletors.size()) return;

            // reverse iterate the deletion queue to execute all the functions
            for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
                (*it)(); //call the function
            }

            deletors.clear();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct QueueFamilyIndices {
        uint32_t graphicsFamily;
        uint32_t presentFamily;
        bool graphicsFamilyHasValue = false;
        bool presentFamilyHasValue = false;
        bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
    };

    struct DeviceVK {
        #ifdef NDEBUG
                const bool enableValidationLayers = false;
        #else
                const bool enableValidationLayers = true;
        #endif
        
        DeviceVK(WindowVK& window);
        ~DeviceVK();

        DeviceVK(const DeviceVK&) = delete;
        DeviceVK& operator=(const DeviceVK&) = delete;
        DeviceVK(DeviceVK&&) = delete;
        DeviceVK& operator=(DeviceVK&&) = delete;

        VkCommandPool getCommandPool() { return commandPool; }
        VkDevice device() { return device_; }
        VkSurfaceKHR surface() { return surface_; }
        VkQueue graphicsQueue() { return graphicsQueue_; }
        VkQueue presentQueue() { return presentQueue_; }
        VmaAllocator allocator() { return allocator_; }

        SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(physicalDevice); }
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(physicalDevice); }
        VkFormat findSupportedFormat(
            const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

        // Buffer Helper Functions
        void createBuffer(
            VkDeviceSize size,
            VkBufferUsageFlags usage,
            VkMemoryPropertyFlags properties,
            VkBuffer& buffer,
            VmaAllocation& allocation,
            VmaMemoryUsage memoryUsage);

        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);

        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        void copyBufferToImage(
            VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);

        void createImageWithInfo(
            const VkImageCreateInfo& imageInfo,
            VkMemoryPropertyFlags properties,
            VkImage& image,
            VmaAllocation& allocation);

        void transitionImageLayout(
            VkImage image,

            VkFormat format,
            VkImageLayout OldLayout, 
            VkImageLayout NewLayout, 
            int layerCount);

        void transitionImageLayout2(
            VkCommandBuffer cmd,
            VkImage image,
            VkImageLayout  oldLayout,       VkImageLayout newLayout,
            VkAccessFlags2 srcAccess,       VkAccessFlags2 dstAccess,
            VkPipelineStageFlags2 srcStage, VkPipelineStageFlags2 dstStage,
            VkImageAspectFlags aspectMask);
 
        void createDeletionQueues(uint64_t amount);
        DeletionQueue& getDeletionQueue() {return deletionQueues[frame_index];};
        void freeDeletionQueue(uint32_t index) {deletionQueues[index].flush();}

        VmaAllocator getVmaAllocator() {return allocator_;}

        inline void setFrameIndex(uint32_t index) {frame_index = index;}

        VkPhysicalDeviceProperties properties;
        
        #ifndef NDEBUG
            struct Logger
            {
                std::ofstream validation;
            };

            void addDebugHandle(
                uint64_t handle, 
                VkObjectType type, 
                const char* name);

            void addDebugObject( 
                uint64_t handle,
                VkObjectType type,
                VmaAllocation allocation,
                const char* name,

                const void* object,
                size_t objectSize);
                
            Logger logger;
        #endif
    private:
        void createInstance();
        void setupDebugMessenger();
        void createSurface(WindowVK& window);
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createCommandPool();
        void createAllocator();
        
        // helper functions
        void createSetDebugNameFunc();
        bool isDeviceSuitable(VkPhysicalDevice device);
        std::vector<const char*> getRequiredExtensions();
        bool checkValidationLayerSupport();
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        void hasGflwRequiredInstanceExtensions();
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

        VkInstance instance_;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkCommandPool commandPool;

        VkDevice device_;
        VkSurfaceKHR surface_;
        VkQueue graphicsQueue_;
        VkQueue presentQueue_;
        VmaAllocator allocator_; 

        PFN_vkSetDebugUtilsObjectNameEXT setDebugNameFunc;

        std::vector<DeletionQueue> deletionQueues;
        uint32_t frame_index = 0;

        const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
        const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
    };
}
