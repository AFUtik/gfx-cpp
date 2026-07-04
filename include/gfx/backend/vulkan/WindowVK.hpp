#pragma once

#include <vulkan/vulkan.h>

struct Window;

namespace gfx::vk {

struct WindowVK {
    WindowVK(Window* window) : window(window) {};
    ~WindowVK() = default;

    void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
	VkExtent2D getExtent();

	bool wasWindowResized();
	void resetWindowResizedFlag();
private:
    Window* window = nullptr;
};

}
