#include "Window.hpp"
#include "pch.hpp"

#include <GLFW/glfw3.h>

Window::~Window() {
	if (window) {
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}

void Window::framebufferResizeCallback(GLFWwindow* glfwWindow, int width, int height) {
	auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
	window->frameBufferResized = true;
	window->width = width;
	window->height = height; 
}

void Window::setCursorMode(int mode) {
	glfwSetInputMode(window, GLFW_CURSOR, mode);
}

bool Window::isShouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::setShouldClose(bool flag) {
	glfwSetWindowShouldClose(window, flag);
}

void Window::swapBuffers() {
	glfwSwapBuffers(window);
}
