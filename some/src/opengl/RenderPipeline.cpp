#include "gfx/backend/opengl/RenderPipeline.hpp"
#include "gfx/backend/opengl/Shader.hpp"

#include <glad/glad.h>

namespace gfx::gl 
{

RenderPipelineGL::RenderPipelineGL(const RenderPipelineDesc& desc)
{
    descriptor = desc;

    program = glCreateProgram();
    glAttachShader(program, desc.vertexState.module.Cast<ShaderGL>()->shader);
    glAttachShader(program, desc.fragState.module.Cast<ShaderGL>()->shader);
    glLinkProgram(program);
}

RenderPipelineGL::~RenderPipelineGL()
{
    glDeleteProgram(program);
}

}