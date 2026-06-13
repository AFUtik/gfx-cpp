#include "backend/opengl/Buffer.hpp"
#include "backend/opengl/Map.hpp"

#include <glad/glad.h>

namespace gfx::gl 
{

BufferGL::BufferGL(const BufferDesc& desc)
{
    glGenBuffers(1, &buffer);

    target = toGLBufferType(desc.type);
    size = desc.size;

    glBindBuffer(target, buffer);

    GLenum usageHint = bufferUsageHint(desc.usage, desc.access);

    glBufferData(target, size, nullptr, usageHint);
}

BufferGL::~BufferGL()
{
    glDeleteBuffers(1, &buffer);
}

void BufferGL::write(const void* data, uint64_t sz, uint64_t offset)
{
    glBindBuffer(target, buffer);
    glBufferSubData(target, offset, sz, data);
}


void* BufferGL::map()
{
    glBindBuffer(target, buffer);
    return glMapBuffer(target, GL_WRITE_ONLY);
}

void BufferGL::unmap()
{
    glUnmapBuffer(target);
}

}