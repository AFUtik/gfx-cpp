#pragma once

#include <vulkan/vulkan.h>

struct Window;

namespace gfx::vk {

struct WindowVK {
    WindowVK(Window* window);
    ~WindowVK() = default;

    WindowVK(const WindowVK&) = delete;
    WindowVK& operator=(const WindowVK&) = delete;

    void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
	VkExtent2D getExtent();

	bool wasWindowResized();
	void resetWindowResizedFlag();
private:
    Window* window = nullptr;
};

}
