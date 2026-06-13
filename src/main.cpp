#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gfx/Backend.hpp"
#include "gfx/Handle.hpp"
#include "gfx/IMesh.hpp"
#include "gfx/Vertex.hpp"

#include <iostream>

// Vertex Shader
const char* vertexShaderSrc = R"(
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 f_color;

void main() {
    f_color = aColor;
    gl_Position = vec4(aPos, 1.0);
}
)";

// Fragment Shader
const char* fragmentShaderSrc = R"(
#version 330 core

in vec3 f_color;

out vec4 FragColor;

void main() {
    FragColor = vec4(f_color, 1.0);
}
)";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main() {
    auto device = gfx::createOpenGLBackend();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(
        window,
        [](GLFWwindow*, int width, int height)
        {
            glViewport(0, 0, width, height);
        }
    );
    
    std::vector<gfx::Vertex> vertices = {
        gfx::Vertex{{0.0f,  0.5f, 0.0f}, {1.0f, 0.0, 0.0}},
        gfx::Vertex{{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0}},
        gfx::Vertex{{0.5f, -0.5f, 0.0f}, {0.0f, 0.0, 1.0f}},
    };

    gfx::VertexLayout layout = gfx::Vertex::getLayout();

    gfx::Handle<gfx::Mesh> mesh = device->createMesh(gfx::MeshDesc{.layout = layout});
    mesh->updateVertices(vertices.data(), 3);

    // compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertexShader);

    // compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fragmentShader);

    // shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        
        // DRAW
        mesh->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}