#include "gfx/backend/opengl/Map.hpp"

#include <glad/glad.h>

namespace gfx::gl 
{

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

}