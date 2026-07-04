#include "gfx/Backend.hpp"
#include "gfx/BindGroup.hpp"
#include "gfx/BindGroupLayout.hpp"
#include "gfx/ColorTarget.hpp"
#include "gfx/Framebuffer.hpp"
#include "gfx/Handle.hpp"
#include "gfx/IImage.hpp"
#include "gfx/IMesh.hpp"
#include "gfx/IShader.hpp"
#include "gfx/PipelineLayout.hpp"
#include "gfx/PipelineState.hpp"
#include "gfx/RenderPass.hpp"
#include "gfx/RenderPipeline.hpp"
#include "gfx/Vertex.hpp"

#include "gfx/backend/vulkan/BackendVK.hpp"
#include "thirdparties/stb_image.h" 

#include "Window.hpp"
#include "Events.hpp"

#include <GLFW/glfw3.h>

// Vertex Shader
const char* vertexShaderSrc = R"(
#version 430 core

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
#version 430 core

in vec3 f_color;
in vec2 tex_coord;

out vec4 FragColor;

layout(binding = 0) uniform sampler2D uTexture;

void main() {
    vec4 color = texture(uTexture, tex_coord) * vec4(f_color, 1.0f);
    FragColor = color;
}
)";

struct Texture
{
    std::unique_ptr<uint8_t> pixels;
    int32_t width;
    int32_t height;
    int32_t channels;
};

const std::string absPath = "/home/afutik/code/cplusplus/GFX/";

int main() {
    Window windowInstance;
    windowInstance.init(800, 600, "GameEngine 0.0.1");

    Events::init(&windowInstance);

    auto device = gfx::createVulkanBackend(&windowInstance);
    gfx::vk::BackendVK* vk = reinterpret_cast<gfx::vk::BackendVK*>(device.get());

    // BindGroup
        // Image loading
    stbi_set_flip_vertically_on_load(true);
    Texture texture;
    texture.pixels.reset(
        stbi_load(
            (absPath+"kharkiv.png").c_str(),
            &texture.width,
            &texture.height,
            &texture.channels,
            4
        )
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
    while (!windowInstance.isShouldClose()) {
        if(Events::jpressed(GLFW_KEY_ESCAPE))
        {
            return 0;
        }

        vk->renderer.beginFrame();

        vk->renderer.beginSwapChainRenderPass();
        vk->renderer.endSwapChainRenderPass();

        vk->renderer.endFrame();

        windowInstance.swapBuffers();
        Events::pullEvents();
    }
    return 0;
}
