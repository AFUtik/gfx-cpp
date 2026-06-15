#include "gfx/backend/opengl/RenderPass.hpp"
#include "gfx/PipelineState.hpp"
#include "gfx/backend/opengl/Framebuffer.hpp"
#include "gfx/backend/opengl/Map.hpp"
#include "gfx/backend/opengl/RenderPipeline.hpp"
#include "gfx/backend/opengl/BindGroupLayout.hpp"
#include "gfx/backend/opengl/Image.hpp"

#include "gfx/BindGroup.hpp"

#include <glad/glad.h>
#include <iostream>

namespace gfx::gl 
{

RenderPassGL::RenderPassGL(const RenderPassDesc& desc)
{
    clearColor = desc.clearColor;
}

RenderPassGL::~RenderPassGL()
{

}

int RenderPassGL::checkCompatibilityWithFBO(Handle<Framebuffer>& framebuffer)
{
    return 0;
}

void RenderPassGL::setRenderPipeline(RenderPipeline* pipeline)
{
    auto* glPipeline = reinterpret_cast<RenderPipelineGL*>(pipeline);
    glUseProgram(glPipeline->program);

    if(currentPipeline != glPipeline)
    {
        PipelineState& p = *pipeline->descriptor.pipelineState.Get();

        if (p.raster.cull == CullMode::None)
            glDisable(GL_CULL_FACE);
        else
        {
            glEnable(GL_CULL_FACE);
            glCullFace(p.raster.cull == CullMode::Back ? GL_BACK : GL_FRONT);
        }

        glFrontFace(
            p.raster.frontFace == FrontFace::Clockwise ?
            GL_CW : GL_CCW
        );

        glPolygonMode(GL_FRONT_AND_BACK,
            p.raster.fill == FillMode::Fill ? GL_FILL : GL_LINE
        );

        glLineWidth(p.raster.lineWidth);

        if (p.raster.depthBias.enable)
        {
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(
                p.raster.depthBias.slopeFactor,
                p.raster.depthBias.constantFactor
            );
        }
        else
        {
            glDisable(GL_POLYGON_OFFSET_FILL);
        }

        if (p.depth.testEnable)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);

        glDepthMask(p.depth.writeEnable ? GL_TRUE : GL_FALSE);

        glDepthFunc(toGLCompare(p.depth.compareOp));

        const auto& a = p.blend.attachments[0];
        if(a.enabled) {
            glEnable(GL_BLEND);
            glBlendFuncSeparate(
                toGLBlendFactor(a.srcColor),
                toGLBlendFactor(a.dstColor),
                toGLBlendFactor(a.srcAlpha),
                toGLBlendFactor(a.dstAlpha)
            );
            glBlendEquationSeparate(
                toGLBlendOp(a.colorOp),
                toGLBlendOp(a.alphaOp)
            );
        }

        if (p.depth.stencilEnable)
            glEnable(GL_STENCIL_TEST);
        else
            glDisable(GL_STENCIL_TEST);
        
        if (p.multisample.sampleCount != SampleCount::x1)
            glEnable(GL_MULTISAMPLE);
        else
            glDisable(GL_MULTISAMPLE);

        currentPipeline = glPipeline;
    }
}

void RenderPassGL::setBindGroup(BindGroup* group)
{

    for(auto& entry : reinterpret_cast<BindGroupLayoutGL*>(group->layout.Get())->layoutEntries)
    {
        switch (entry.type.index()) {
            case BindingTypeEnum::BINDING_TYPE_BUFFER : {
                return;
            }
            case BindingTypeEnum::BINDING_TYPE_IMAGE: {
                glActiveTexture(GL_TEXTURE0 + entry.binding);
                glBindTexture(GL_TEXTURE_2D, reinterpret_cast<ImageGL*>(group->entries[entry.binding].resource.Get())->tex);
                return;
            }
        }
    }
}


void RenderPassGL::begin(const Framebuffer* framebuffer)
{
    const FramebufferGL* glFbo = reinterpret_cast<const FramebufferGL*>(framebuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, glFbo->fbo);
    glViewport(0, 0, glFbo->fbo_width, glFbo->fbo_height);

    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderPassGL::end()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} 