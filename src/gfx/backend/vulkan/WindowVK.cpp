#include "gfx/backend/vulkan/WindowVK.hpp"

#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace gfx::vk {

void WindowVK::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) 
{
	if (glfwCreateWindowSurface(instance, window->getGlfwWindow(), nullptr, surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to craete window surface");
	}
}

VkExtent2D WindowVK::getExtent() 
{ 
    return { static_cast<uint32_t>(window->getWidth()), static_cast<uint32_t>(window->getHeight()) }; 
}

bool WindowVK::wasWindowResized() { return window->wasWindowResized(); }

void WindowVK::resetWindowResizedFlag() { window->resetWindowResizedFlag(); }


}
