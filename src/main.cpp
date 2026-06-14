#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gfx/Backend.hpp"
#include "gfx/Handle.hpp"
#include "gfx/IImage.hpp"
#include "gfx/IMesh.hpp"
#include "gfx/Vertex.hpp"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "thirdparties/stb_image.h"

// Vertex Shader
const char* vertexShaderSrc = R"(
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aColor;

out vec3 f_color;
out vec2 tex_coord;

void main() {
    f_color   = aColor;
    tex_coord = aUv;

    gl_Position = vec4(aPos, 1.0);
}
)";

// Fragment Shader
const char* fragmentShaderSrc = R"(
#version 330 core

in vec3 f_color;
in vec2 tex_coord;

out vec4 FragColor;

uniform sampler2D uTexture;

void main() {
    vec4 color = texture(uTexture, tex_coord) * vec4(f_color, 1.0f);
    FragColor = color;
}
)";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

struct Texture
{
    std::unique_ptr<uint8_t> pixels;
    int32_t width;
    int32_t height;
    int32_t channels;
};

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
        gfx::Vertex{{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
        gfx::Vertex{{ 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
        gfx::Vertex{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
        gfx::Vertex{{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
    };
    std::vector<uint32_t> indices = {
        0, 1, 3,
        1, 2, 3
    };

    gfx::Handle<gfx::MeshDesc> desc = device->meshDescHandle(
        gfx::MeshDesc{
            .layout = gfx::Vertex::getLayout(),
            .indexStride = sizeof(uint32_t)
        }
    );

    gfx::Handle<gfx::Mesh> mesh = device->createMesh(desc);
    mesh->updateVertices(vertices.data(), vertices.size());
    mesh->updateIndexes (indices.data(), indices.size());

    stbi_set_flip_vertically_on_load(true);
    Texture texture;
    texture.pixels.reset(
        stbi_load(
            "/home/afutik/cplusplus/GFX/kharkiv.png",
            &texture.width,
            &texture.height,
            &texture.channels,
            4
        )
    );

    gfx::Handle<gfx::Image> image = device->createImage(
        gfx::ImageDesc{
            .width    = (uint32_t)texture.width,
            .height   = (uint32_t)texture.height,
            .channels = 4,
            .filter   = gfx::ImageFilter::NEAREST
        }
    );
    image->write(texture.pixels.get());

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLint texLoc = glGetUniformLocation(shaderProgram, "uTexture");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        
        // DRAW
        image->bind();
        glUniform1i(texLoc, 0);

        mesh->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}