#pragma once

#include "gfx/IRenderer.hpp"

#include "pch.hpp"

struct VkRenderPass_T;
using VkRenderPass = VkRenderPass_T*;

struct VkCommandBuffer_T;
using VkCommandBuffer = VkCommandBuffer_T*;

namespace gfx::vk {
	class SwapChain;
	class DescriptorPoolManager;

    struct WindowVK;
	struct DeviceVK;

	class RendererVK : public Renderer {
	public:
		RendererVK(DeviceVK& device, WindowVK& window);
		~RendererVK();

		RendererVK(const RendererVK&) = delete;
		RendererVK& operator=(const RendererVK&) = delete;

		VkRenderPass getSwapChainRenderPass();
		bool isFrameInProgress() const { return isFrameStarted; }

		DescriptorPoolManager* getDescriptorPool() { return descriptorPoolManager.get(); }
		SwapChain* getSwapChain() {return swapchain.get();}

		VkCommandBuffer getCurrentCommandBuffer() const { 
			assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
			return commandBuffers[currentFrameIndex]; 
		}

		int getFrameIndex() const { 
			assert(isFrameStarted && "Cannot get frame buffer index when frame not in progress");
			return currentFrameIndex; 
		}

		Frame& beginFrame() override;
		void   endFrame()   override;

		void beginRendering();
		void endRendering();
	private:
		void createCommandBuffers();
		void recreateSwapChain();
		void freeCommandBuffers();

		DeviceVK& device;
		WindowVK& window;

		Frame frame;

		std::unique_ptr<SwapChain> swapchain;

		std::vector<VkCommandBuffer> commandBuffers;

		std::unique_ptr<DescriptorPoolManager> descriptorPoolManager;

		uint32_t currentImageIndex;
		int currentFrameIndex = 0;
		bool isFrameStarted = false;
	};
}
