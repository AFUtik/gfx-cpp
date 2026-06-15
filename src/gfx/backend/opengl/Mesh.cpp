#include "gfx/IMesh.hpp"
#include "gfx/Vertex.hpp"

#include "gfx/backend/opengl/BackendGL.hpp"
#include "gfx/backend/opengl/Buffer.hpp"
#include "gfx/backend/opengl/Map.hpp"
#include "gfx/backend/opengl/Mesh.hpp"

#include <glad/glad.h>

uint32_t nextPow2(uint32_t x) {
    if (x == 0) return 1;
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x++;
    return x;
}

namespace gfx::gl 
{

MeshDescGL::MeshDescGL(const MeshDesc& desc)
{
    glIndexType = toGLUnsignedType(desc.indexStride);

    this->layout      = desc.layout;
    this->indexStride = desc.indexStride; 
}

MeshGL::MeshGL(BackendGL& device, const Handle<MeshDescGL>& desc) : device(device), descriptor(desc)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    vbo = device.createBuffer(
        BufferDesc{
            .type   = gfx::BufferType::Vertex,
            .usage  = gfx::BufferUsage::Static,
            .access = gfx::BufferAccess::GPUOnly,
            .size   = 512,
            .cpuVisible = false
        }
    );
    ebo = device.createBuffer(
        BufferDesc{
            .type   = gfx::BufferType::Index,
            .usage  = gfx::BufferUsage::Static,
            .access = gfx::BufferAccess::GPUOnly,
            .size   = 512,
            .cpuVisible = false
        }
    );

    for (const auto& attr : desc->layout.attributes)
    {
        glEnableVertexAttribArray(attr.location);

        glVertexAttribPointer(
            attr.location,
            (attr.format == VertexFormat::Float3 ? 3 :
             attr.format == VertexFormat::Float2 ? 2 : 4),
            GL_FLOAT,
            GL_FALSE,
            desc->layout.stride,
            (void*)(uintptr_t)attr.offset
        );
    }

    glBindVertexArray(0);
}

MeshGL::~MeshGL()
{
    glDeleteVertexArrays(1, &vao);
}

void MeshGL::updateVertices(const void* data, uint64_t count)
{
    vertexCount = count;
    if(!vbo || vertexCount*descriptor->layout.stride > vbo->getSize())
    {
        vbo = device.createBuffer(
            BufferDesc{
                .type   = gfx::BufferType::Vertex,
                .usage  = gfx::BufferUsage::Static,
                .access = gfx::BufferAccess::GPUOnly,
                .size   = nextPow2(vertexCount),
                .cpuVisible = false
            }
        );
    }
    vbo->write(data, count*descriptor->layout.stride, 0);
}

void MeshGL::updateIndexes(const void* data, uint64_t count)
{
    indexCount = count;
    if(!ebo || indexCount*descriptor->indexStride > ebo->getSize())
    {
        ebo = device.createBuffer(
            BufferDesc{
                .type   = gfx::BufferType::Index,
                .usage  = gfx::BufferUsage::Static,
                .access = gfx::BufferAccess::GPUOnly,
                .size   = nextPow2(indexCount),
                .cpuVisible = false
            }
        );
    }
    ebo->write(data, count*descriptor->indexStride, 0);
}

void MeshGL::draw()
{
    glBindVertexArray(vao);
    if(ebo)
    {
        glDrawElements(
            GL_TRIANGLES,
            indexCount,
            descriptor->glIndexType,
            0
        );
    }
    else 
    {
        glDrawArrays(
            GL_TRIANGLES,
            0,
            vertexCount
        );
    }
	glBindVertexArray(0);
}

void MeshGL::draw(uint32_t instanceCount, uint32_t baseInstanceOffset)
{
    glBindVertexArray(vao);
    if(ebo)
    {
        glDrawElementsInstancedBaseInstance(
            GL_TRIANGLES,
            indexCount,
            descriptor->glIndexType,
            0,
            instanceCount,
            baseInstanceOffset
        );
    }
    else 
    {
        glDrawArraysInstancedBaseInstance(
            GL_TRIANGLES,
            0,
            vertexCount,
            instanceCount,
            baseInstanceOffset
        );
    }
	glBindVertexArray(0);
}

Buffer* MeshGL::getVertexBuffer()
{
    return vbo.Get();
}

Buffer* MeshGL::getIndexBuffer()
{
    return nullptr;
}

Buffer* MeshGL::getInstanceBuffer()
{
    return nullptr;
}

}