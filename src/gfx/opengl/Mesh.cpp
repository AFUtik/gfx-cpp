#include "gfx/IMesh.hpp"
#include "gfx/Vertex.hpp"

#include "gfx/backend/opengl/BackendGL.hpp"
#include "gfx/backend/opengl/Buffer.hpp"
#include "gfx/backend/opengl/Mesh.hpp"

#include <glad/glad.h>

namespace gfx::gl 
{

MeshGL::MeshGL(BackendGL& device, const MeshDesc& desc) : device(device), layout(desc.layout)
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

    for (const auto& attr : desc.layout.attributes)
    {
        glEnableVertexAttribArray(attr.location);

        glVertexAttribPointer(
            attr.location,
            (attr.format == VertexFormat::Float3 ? 3 :
             attr.format == VertexFormat::Float2 ? 2 : 4),
            GL_FLOAT,
            GL_FALSE,
            desc.layout.stride,
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
    if(vertexCount*layout.stride > vbo->getSize())
    {
        vbo = device.createBuffer(
            BufferDesc{
                .type   = gfx::BufferType::Vertex,
                .usage  = gfx::BufferUsage::Static,
                .access = gfx::BufferAccess::GPUOnly,
                .size   = 512,
                .cpuVisible = false
            }
        );
    }
    vbo->write(data, count*layout.stride, 0);
}

void MeshGL::draw()
{
    glBindVertexArray(vao);
	glDrawArrays(
        GL_TRIANGLES,
        0,
        vertexCount
    );
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