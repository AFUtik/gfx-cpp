#pragma once

struct GLFWwindow;

class Window {
public:
	Window() {};
	~Window();

    void setWidth(int width) {this->width = width;};
    void setHeight(int height) {this->height = height;};
    void setTitle(const char* title) {this->title = title;};
    void setIcon(const unsigned char* pixels) {};
    void setGlfwWindow(GLFWwindow* window) {this->window = window;}

	bool isShouldClose();
	void setShouldClose(bool flag);
	void swapBuffers();
	void setCursorMode(int mode);
	bool wasWindowResized() { return frameBufferResized; }
	void resetWindowResizedFlag() { frameBufferResized = false; }

	int getWidth()  {return width;}
	int getHeight() {return height;}
    const char* getTitle() {return title;}
	GLFWwindow* getGlfwWindow() {return window;}
private:
	static void framebufferResizeCallback(GLFWwindow* glfwWindow, int width, int height);
	
	int width  = 800;
	int height = 600;
    const char* title  = nullptr; 
	GLFWwindow* window = nullptr;
	bool frameBufferResized = false;

    friend struct Events;
};

