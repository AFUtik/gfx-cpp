#include "gfx/backend/vulkan/Renderer.hpp"
#include "gfx/backend/vulkan/Device.hpp"
#include "gfx/backend/vulkan/Swapchain.hpp"
#include "gfx/backend/vulkan/Descriptors.hpp"
#include "gfx/backend/vulkan/Window.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#include "pch.hpp"

namespace gfx::vk {

RendererVK::RendererVK(DeviceVK& device, WindowVK& window, const SwapchainDesc& swapchainDesc) : device(device), window(window) {
	recreateSwapChain(swapchainDesc);
	createCommandBuffers();
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

void RendererVK::recreateSwapChain(const SwapchainDesc& desc) {
	auto extent = window.getExtent();
	while (extent.width == 0 || extent.height == 0) {
		extent = window.getExtent();
		glfwWaitEvents();
	}
	vkDeviceWaitIdle(device.device());
	
	if (swapchain == nullptr) {
		swapchain = std::make_unique<SwapChain>(device, desc, extent);
	}
	else {
		std::shared_ptr<SwapChain> oldSwapChain = std::move(swapchain);
		swapchain = std::make_unique<SwapChain>(device, desc, extent, oldSwapChain);

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

void RendererVK::updateSwapchain(const SwapchainDesc& desc)
{
    assert(!isFrameStarted && "Can't call updateSwapchain when frame is started.");
    recreateSwapChain(desc);
}


Frame& RendererVK::beginFrame() {
	assert(!isFrameStarted && "Can't call beginFrame while already in progress");
	auto result = swapchain->acquireNextImage(&currentImageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		recreateSwapChain(swapchain->getSwapchainDesc());
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
	
	frame.cmdBuf     = reinterpret_cast<CommandBuffer>(commandBuffer);
	frame.imageIndex = currentFrameIndex;
    return frame;
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
		recreateSwapChain(swapchain->getSwapchainDesc());
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}

	isFrameStarted = false;
	currentFrameIndex = (currentFrameIndex + 1) % SwapChain::MAX_FRAMES_IN_FLIGHT;

	frame.cmdBuf = VK_NULL_HANDLE;
	
}

void RendererVK::beginRendering() 
{
    VkCommandBuffer commandBuffer = reinterpret_cast<VkCommandBuffer>(frame.cmdBuf);

    device.transitionImageLayout2(
            commandBuffer,
            swapchain->getImage(currentImageIndex),
            swapchain->getImageLayout(currentImageIndex), 
            VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,

            VK_ACCESS_2_NONE, 
            VK_ACCESS_2_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,

            VK_PIPELINE_STAGE_2_NONE, 
            VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,

            VK_IMAGE_ASPECT_COLOR_BIT);
    swapchain->setImageLayout(currentImageIndex, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

    if(swapchain->getDepthImageLayout(currentImageIndex) != VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL)
    {
        device.transitionImageLayout2(
                commandBuffer,
                swapchain->getDepthImage(currentImageIndex),
                swapchain->getDepthImageLayout(currentImageIndex),
                VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,

                VK_ACCESS_2_NONE,
                VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,

                VK_PIPELINE_STAGE_2_NONE,
                VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT,

                VK_IMAGE_ASPECT_DEPTH_BIT
                );
        swapchain->setDepthImageLayout(currentImageIndex, VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL);
    }

    assert(isFrameStarted);
    assert(commandBuffer == getCurrentCommandBuffer());

    VkRenderingAttachmentInfo colorAttachment{};
    colorAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
    colorAttachment.imageView = swapchain->getImageView(currentImageIndex);
    colorAttachment.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    colorAttachment.loadOp  = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

    colorAttachment.clearValue.color = {{0.1f, 0.1f, 0.1f, 1.0f}};

    VkRenderingAttachmentInfo depthAttachment{};
    depthAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
    depthAttachment.imageView = swapchain->getDepthImageView(currentImageIndex);
    depthAttachment.imageLayout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;

    depthAttachment.loadOp  = VK_ATTACHMENT_LOAD_OP_CLEAR;
    depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

    depthAttachment.clearValue.depthStencil = {1.0f, 0};

    VkRenderingInfo renderingInfo{};
    renderingInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO;

    renderingInfo.renderArea.offset = {0, 0};
    renderingInfo.renderArea.extent = swapchain->getSwapChainExtent();

    renderingInfo.layerCount = 1;

    renderingInfo.colorAttachmentCount = 1;
    renderingInfo.pColorAttachments = &colorAttachment;

    renderingInfo.pDepthAttachment = &depthAttachment;
    renderingInfo.pStencilAttachment = nullptr;

    vkCmdBeginRendering(commandBuffer, &renderingInfo);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width  = static_cast<float>(swapchain->getSwapChainExtent().width);
    viewport.height = static_cast<float>(swapchain->getSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = swapchain->getSwapChainExtent();

    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}

void RendererVK::endRendering() { 
    VkCommandBuffer commandBuffer = reinterpret_cast<VkCommandBuffer>(frame.cmdBuf);

	assert(isFrameStarted && "Can't call endSwapChainRenderPass while already in progress");
	assert(commandBuffer == getCurrentCommandBuffer() && "can't end render pass on command buffer from a different frame");

	vkCmdEndRendering(commandBuffer);

    device.transitionImageLayout2(
        commandBuffer,
        swapchain->getImage(currentImageIndex),
            VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, 
            VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,

            VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,
            VK_ACCESS_2_NONE,

            VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
            VK_PIPELINE_STAGE_2_NONE,

            VK_IMAGE_ASPECT_COLOR_BIT);

    swapchain->setImageLayout(currentImageIndex, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
}

}
