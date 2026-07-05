#include "gfx/Backend.hpp"
#include "gfx/Vertex.hpp"

#include "gfx/backend/vulkan/BackendVK.hpp"
#include "thirdparties/stb_image.h" 

#include "Window.hpp"
#include "Events.hpp"

#include <GLFW/glfw3.h>

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
    windowInstance.setWidth(800);
    windowInstance.setHeight(600);
    windowInstance.setTitle("Circuit Craft 1.0.0");

    auto device = gfx::createVulkanBackend(&windowInstance);
    gfx::vk::BackendVK* vk = reinterpret_cast<gfx::vk::BackendVK*>(device.get());

    Events::init(&windowInstance);
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
