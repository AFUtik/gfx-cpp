#include "gfx/Backend.hpp"
#include "gfx/BindGroup.hpp"
#include "gfx/BindGroupLayout.hpp"
#include "gfx/IBuffer.hpp"
#include "gfx/IImage.hpp"
#include "gfx/IMesh.hpp"
#include "gfx/IShader.hpp"
#include "gfx/PipelineLayout.hpp"
#include "gfx/SwapChain.hpp"
#include "gfx/Vertex.hpp"
#include "gfx/PipelineState.hpp"
#include "gfx/RenderPipeline.hpp"

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

std::vector<char> readFile(const std::string& filepath) {
    std::ifstream file{ filepath, std::ios::ate | std::ios::binary };

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file: " + filepath);
    }

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}

const std::string absPath = "/home/afutik/code/cplusplus/GFX/";
const std::string resPath = "/home/afutik/code/cplusplus/GFX/resources/";

int main() {
    Window windowInstance;
    windowInstance.setWidth(800);
    windowInstance.setHeight(600);
    windowInstance.setTitle("Circuit Craft 1.0.0");

    auto device = gfx::createVulkanBackend(&windowInstance);
    device->updateSwapchain(gfx::SwapchainDesc{
                .mode = gfx::PresentMode::Immediate
            });

    gfx::vk::BackendVK* vk = reinterpret_cast<gfx::vk::BackendVK*>(device.get());
    
    std::vector<char> vertShaderSpirv = readFile(resPath+"shaders/vk/shader.vert.spv");
    std::vector<char> fragShaderSpirv = readFile(resPath+"shaders/vk/shader.frag.spv");

    gfx::Handle<gfx::Shader> vertShader = device->createShader(gfx::ShaderDesc{
                .name       = "Vertex Shader",
                .spirv      = reinterpret_cast<const uint32_t*>(vertShaderSpirv.data()),
                .spirv_size = vertShaderSpirv.size(),
                .glsl       = "",
                .stage      = gfx::ShaderStage::Vertex
            });

    gfx::Handle<gfx::Shader> fragShader = device->createShader(gfx::ShaderDesc{
                .name       = "Fragment Shader",
                .spirv      = reinterpret_cast<const uint32_t*>(fragShaderSpirv.data()),
                .spirv_size = fragShaderSpirv.size(),
                .glsl       = "",
                .stage      = gfx::ShaderStage::Fragment
            }); 


    gfx::Handle<gfx::BindGroupLayout> bindGroupLayout = device->createBindGroupLayout(gfx::BindGroupLayoutDesc{
                .entries = {
                    gfx::BindGroupLayoutEntry{
                        .type = gfx::TextureTypeStruct{.sample_type = gfx::TextureSampleType::Float},
                        .visibility = gfx::ShaderStage::Fragment, 
                        .binding = 0,
                        .uniformName = ""
                    }
                },
                .set = 0
            });

    gfx::Handle<gfx::PipelineLayout> pipelineLayout = device->createPipelineLayout(gfx::PipelineLayoutDesc{
                .layouts = {bindGroupLayout}
            });

    gfx::RenderPipelineDesc pipelineDesc {
        .vertexState = gfx::VertexState {
            .module = vertShader,
            .layout = gfx::Vertex::getLayout()
        },
        .fragState = gfx::FragmentState {
            .module = fragShader
        },
        .pipelineState  = {},
        .pipelineLayout = pipelineLayout
    };

    gfx::Handle<gfx::RenderPipeline> pipeline = device->createRenderPipeline(pipelineDesc);

    Events::init(&windowInstance);
    // BindGroup
        // Image loading
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
    
    gfx::Handle<gfx::Sampler> sampler = device->createSampler(gfx::SamplerDesc{
                .filter = gfx::ImageFilter::NEAREST
            });

    gfx::Handle<gfx::Image> image = device->createImage(gfx::ImageDesc{
                .width  = (uint32_t)texture.width,
                .height = (uint32_t)texture.height,
                .format = gfx::ImageFormat::RGBA8_SRGB
            });

    image->write(texture.pixels.get());
    image->setSampler(sampler);

    gfx::Handle<gfx::BindGroup> bindGroup = device->createBindGroup(bindGroupLayout);
    bindGroup->setImage(0, image);
    bindGroup->write();

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

    gfx::Handle<gfx::Mesh> mesh = device->createMesh(gfx::MeshDesc{
                .layout = gfx::Vertex::getLayout(),
                .indexStride = sizeof(uint32_t),
                .bufferUsage = gfx::BufferUsage::Static
            });
    mesh->updateVertices(vertices.data(), vertices.size());
    mesh->updateIndexes(indices.data(), indices.size());

    while (!windowInstance.isShouldClose()) {
        if(Events::jpressed(GLFW_KEY_ESCAPE))
        {
            return 0;
        }

        gfx::Frame& frame = vk->renderer.beginFrame();
        vk->renderer.beginRendering();

        pipeline->bind(frame.cmdBuf);
        pipeline->bindGroup(frame.cmdBuf, bindGroup);

        mesh->draw(frame.cmdBuf);

        vk->renderer.endRendering();
        vk->renderer.endFrame();

        windowInstance.swapBuffers();
        Events::pullEvents();
    }
    return 0;
}
