#pragma once

#include "gfx/Handle.hpp"
#include "gfx/Framebuffer.hpp"

namespace gfx::gl
{

struct ImageGL;
struct BackendGL;

struct FramebufferGL : Framebuffer
{
    FramebufferGL(BackendGL&, const FramebufferDesc&);
    ~FramebufferGL();
    
    FramebufferGL(BackendGL& device) : device(device) {};

    Image& getImage(uint32_t attachment) override;
    Image& getDepthImage()               override;

    inline void resize(uint32_t width, uint32_t height) override
    {
        fbo_width  = width;
        fbo_height = height;
    }
private:
    void createImages(const std::vector<ColorTargetDesc>&);
    void createDepthResources(const DepthTargetDesc&);

    void createFBO();

    BackendGL& device;

    std::vector<Handle<ImageGL>> images;
    Handle<ImageGL>              depthImage;

    // GL OBJECT //
    uint32_t fbo        = 0;
    uint32_t fbo_width  = 800;
    uint32_t fbo_height = 600;

    friend struct BackendGL;
    friend struct RenderPassGL;
};

};