#include "gfx/backend/opengl/Framebuffer.hpp"
#include "gfx/IImage.hpp"
#include "gfx/backend/opengl/BackendGL.hpp"
#include "gfx/backend/opengl/Image.hpp"

#include <glad/glad.h>
#include <iostream>

namespace gfx::gl 
{

FramebufferGL::FramebufferGL(BackendGL& device, const FramebufferDesc& desc) : device(device)
{
    createImages(desc.colorDescs);
    createDepthResources(desc.depthDesc); 

    createFBO();
}

FramebufferGL::~FramebufferGL()
{
    if(fbo) glDeleteFramebuffers(1, &fbo);
}

void FramebufferGL::createImages(const std::vector<ColorTargetDesc>& descs)
{
    for(auto& desc : descs)
    {
        images.push_back(
            device.createImage(
                ImageDesc{
                    .width    = desc.width,
                    .height   = desc.height,
                    .channels = 4,
                    .filter   = ImageFilter::LINEAR
                }
            ).Cast<ImageGL>()
        );
    }
}

void FramebufferGL::createDepthResources(const DepthTargetDesc& desc)
{
    depthImage = device.createImage(
        ImageDesc{
            .width    = desc.width,
            .height   = desc.height,
            .channels = 4,
            .filter   = ImageFilter::LINEAR
        }
    ).Cast<ImageGL>();
}

void FramebufferGL::createFBO()
{
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    std::vector<GLenum> drawBuffers;
    for (size_t i = 0; i < images.size(); i++)
    {
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0 + i,
            GL_TEXTURE_2D,
            images[i]->tex,
            0
        );
        drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + i);
    }

    if (!drawBuffers.empty())
    {
        glDrawBuffers(drawBuffers.size(), drawBuffers.data());
    }
    else
    {
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }

    if (depthImage)
    {

        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,
            GL_TEXTURE_2D,
            depthImage->tex,
            0
        );
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << ("FBO not complete!\n") << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Image& FramebufferGL::getImage(uint32_t attachment)
{
    return *images[attachment].Get();
}

Image& FramebufferGL::getDepthImage() 
{
    return *depthImage.Get();
}

}