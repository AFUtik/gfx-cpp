#include "gfx/backend/vulkan/Window.hpp"

#include "Window.hpp"
#include <GLFW/glfw3.h>

#include "pch.hpp"

namespace gfx::vk {

WindowVK::WindowVK(Window* _window) : window(_window) {
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		exit(1);
	}

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	window->setGlfwWindow(glfwCreateWindow(
                window->getWidth(),
                window->getHeight(),
                window->getTitle(),
                nullptr,
                nullptr
                ));

    if (window->getGlfwWindow() == nullptr) {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        exit(1);
    }
	glfwSetWindowUserPointer(window->getGlfwWindow(), window);
}

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
