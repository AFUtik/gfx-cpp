#include "gfx/backend/opengl/Shader.hpp"
#include "gfx/backend/opengl/Map.hpp"

#include <glad/glad.h>
#include <iostream>

namespace gfx::gl 
{

ShaderGL::ShaderGL(const ShaderDesc& desc)
{
    GLenum shaderType = toGLShaderType(desc.stage); 
    GLint success;
    GLchar infoLog[512];

    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &desc.glsl, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "SHADER: compilatinon failed. SHADER_NAME: " << desc.name << std::endl;
        std::cerr << infoLog << std::endl;
        exit(1);
    }
}

ShaderGL::~ShaderGL()
{
    glDeleteShader(shader);
}

}