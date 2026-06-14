#include "gfx/backend/opengl/Map.hpp"

#include <glad/glad.h>

namespace gfx::gl 
{

GLenum ToGLShaderType(ShaderStage stage)
{
    switch (stage)
    {
        case ShaderStage::Vertex:         return GL_VERTEX_SHADER;
        case ShaderStage::Fragment:       return GL_FRAGMENT_SHADER;
        case ShaderStage::Geometry:       return GL_GEOMETRY_SHADER;
        case ShaderStage::TessControl:    return GL_TESS_CONTROL_SHADER;
        case ShaderStage::TessEvaluation: return GL_TESS_EVALUATION_SHADER;
        case ShaderStage::Compute:        return GL_COMPUTE_SHADER;
        default:                          return 0;
    }
}

uint32_t toGLUnsignedType(uint64_t size)
{
    switch (size) 
    {
        case 1: return GL_UNSIGNED_BYTE;
        case 2: return GL_UNSIGNED_SHORT;
        case 4: return GL_UNSIGNED_INT;
        default: return 0;
    }
}

uint32_t toGLBufferType(BufferType type)
{
    switch (type)
    {
        case BufferType::Vertex:  return GL_ARRAY_BUFFER;
        case BufferType::Index:   return GL_ELEMENT_ARRAY_BUFFER;
        case BufferType::Uniform: return GL_UNIFORM_BUFFER;
        case BufferType::Storage: return GL_SHADER_STORAGE_BUFFER;
        case BufferType::Staging: return GL_ARRAY_BUFFER;
    }
    return GL_ARRAY_BUFFER;
}

uint32_t bufferUsageHint(BufferUsage usage, BufferAccess access)
{
    if (access == BufferAccess::GPUOnly)
        return GL_STATIC_DRAW;

    if (access == BufferAccess::CPUToGPU)
        return (usage == BufferUsage::Dynamic)
            ? GL_DYNAMIC_DRAW
            : GL_STREAM_DRAW;

    return GL_DYNAMIC_READ; // GPU → CPU
}

void applyBlendMode(BlendMode mode)
{
    switch (mode)
    {
        case BlendMode::Opaque:
        case BlendMode::None:
            glDisable(GL_BLEND);
            break;

        case BlendMode::Alpha:
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBlendEquation(GL_FUNC_ADD);
            break;

        case BlendMode::Additive:
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glBlendEquation(GL_FUNC_ADD);
            break;

        case BlendMode::Multiply:
            glEnable(GL_BLEND);
            glBlendFunc(GL_DST_COLOR, GL_ZERO);
            break;

        case BlendMode::Screen:
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
            break;
    }
}

}