#include "gfx/backend/opengl/RenderPass.hpp"
#include "gfx/backend/opengl/Image.hpp"

#include <glad/glad.h>
#include <iostream>

namespace gfx::gl 
{

RenderPassGL::RenderPassGL(const RenderPassDesc& desc)
{
    this->clearColor = desc.clearColor;
    createFBO(desc);
}

RenderPassGL::~RenderPassGL()
{
    if(fbo) glDeleteFramebuffers(1, &fbo);
}

void RenderPassGL::createFBO(const RenderPassDesc& desc)
{
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    std::vector<GLenum> drawBuffers;
    for (size_t i = 0; i < desc.colorTargets.size(); i++)
    {
        const ImageGL* image = reinterpret_cast<const ImageGL*>(desc.colorTargets[i].Get());
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0 + i,
            GL_TEXTURE_2D,
            image->tex,
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

    if (desc.depthTarget)
    {
        const ImageGL* depthImage = reinterpret_cast<const ImageGL*>(desc.depthTarget.Get());
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

void RenderPassGL::begin()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, fbo_width, fbo_height);

    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderPassGL::end()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ScreenRenderPassGL::ScreenRenderPassGL(const RenderPassDesc& desc) : RenderPassGL()
{
    clearColor = desc.clearColor;
    fbo        = 0;
}

}