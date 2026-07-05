#include "gfx/backend/vulkan/Renderer.hpp"
#include "gfx/backend/vulkan/Device.hpp"
#include "gfx/backend/vulkan/SwapChain.hpp"
#include "gfx/backend/vulkan/Descriptors.hpp"
#include "gfx/backend/vulkan/Window.hpp"

#include <GLFW/glfw3.h>

#include "pch.hpp"

namespace gfx::vk {

RendererVK::RendererVK(DeviceVK& device, WindowVK& window) : device(device), window(window) {
	recreateSwapChain();
	createCommandBuffers();
	descriptorPoolManager = DescriptorPoolManager::Builder(device)
		.setMaxSets(1024)
		.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1024)
		.addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1024)
		.addPoolSize(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1024)
		.build();
}

RendererVK::~RendererVK() {

	freeCommandBuffers();
}

VkRenderPass RendererVK::getSwapChainRenderPass() 
{ 
	return swapchain->getRenderPass(); 
}

void RendererVK::createCommandBuffers() {
	commandBuffers.resize(SwapChain::MAX_FRAMES_IN_FLIGHT);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = device.getCommandPool();
	allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

	if (vkAllocateCommandBuffers(device.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers");
	}
}

void RendererVK::recreateSwapChain() {
	auto extent = window.getExtent();
	while (extent.width == 0 || extent.height == 0) {
		extent = window.getExtent();
		glfwWaitEvents();
	}
	vkDeviceWaitIdle(device.device());
	
	if (swapchain == nullptr) {
		swapchain = std::make_unique<SwapChain>(device, extent, PresentMode::FIFO);
	}
	else {
		std::shared_ptr<SwapChain> oldSwapChain = std::move(swapchain);
		swapchain = std::make_unique<SwapChain>(device, extent, PresentMode::FIFO, oldSwapChain);

		if (!oldSwapChain->compareSwapFormats(*swapchain.get())) {
			throw std::runtime_error("Swap chain image(or depth) format has changed");
		}
	}
}

void RendererVK::freeCommandBuffers() {
	vkFreeCommandBuffers(
		device.device(),
		device.getCommandPool(),
		static_cast<uint32_t>(commandBuffers.size()),
		commandBuffers.data());
	commandBuffers.clear();
}

Frame& RendererVK::beginFrame() {
	assert(!isFrameStarted && "Can't call beginFrame while already in progress");
	auto result = swapchain->acquireNextImage(&currentImageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		recreateSwapChain();
		return frame;
	}

	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}
	
	isFrameStarted = true;

	auto commandBuffer = getCurrentCommandBuffer();
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}
	
	frame.cmdBuf     = reinterpret_cast<CommandBuffer*>(commandBuffer);
	frame.imageIndex = currentFrameIndex;
}

void RendererVK::endFrame() {
	assert(isFrameStarted && "Can't call endFrame while already in progress");
	auto commandBuffer = getCurrentCommandBuffer();
	if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to record command buffer!");
	}
	auto result = swapchain->submitCommandBuffers(&commandBuffer, &currentImageIndex);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR ||
		window.wasWindowResized()) {
		window.resetWindowResizedFlag();
		recreateSwapChain();
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}

	isFrameStarted = false;
	currentFrameIndex = (currentFrameIndex + 1) % SwapChain::MAX_FRAMES_IN_FLIGHT;

	frame.commandBuffer = VK_NULL_HANDLE;
	
}

void RendererVK::beginSwapChainRenderPass() {
	assert(isFrameStarted && "Can't call beginSwapChainRenderPass while already in progress");
	assert(frame.commandBuffer == getCurrentCommandBuffer() && "can't begin render pass on command buffer from a different frame");

	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = swapchain->getRenderPass();
	renderPassInfo.framebuffer = swapchain->getFrameBuffer(currentImageIndex);

	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = swapchain->getSwapChainExtent();

	std::array<VkClearValue, 2> clearValues{};
	clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
	clearValues[1].depthStencil = { 1.0f, 0 };
	renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
	renderPassInfo.pClearValues = clearValues.data();

	vkCmdBeginRenderPass(frame.commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(swapchain->getSwapChainExtent().width);
	viewport.height = static_cast<float>(swapchain->getSwapChainExtent().height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	VkRect2D scissor{ {0, 0}, swapchain->getSwapChainExtent() };
	vkCmdSetViewport(frame.commandBuffer, 0, 1, &viewport);
	vkCmdSetScissor(frame.commandBuffer, 0, 1, &scissor);
}

void RendererVK::endSwapChainRenderPass() {
	assert(isFrameStarted && "Can't call endSwapChainRenderPass while already in progress");
	assert(frame.commandBuffer == getCurrentCommandBuffer() && "can't end render pass on command buffer from a different frame");
	vkCmdEndRenderPass(frame.commandBuffer);
}

}
