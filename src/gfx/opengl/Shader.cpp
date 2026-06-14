#pragma once

#include "gfx/backend/opengl/Shader.hpp"
#include "gfx/backend/opengl/Map.hpp"

#include <glad/glad.h>

namespace gfx::gl 
{

ShaderGL::ShaderGL(const ShaderDesc& desc)
{
    GLenum shaderType = toGLShaderType(desc.stage); 

    unsigned int vertexShader = glCreateShader(shaderType);
    glShaderSource(vertexShader, 1, &desc.glsl, nullptr);
    glCompileShader(vertexShader);
}

ShaderGL::~ShaderGL()
{
    glDeleteShader(shader);
}

}