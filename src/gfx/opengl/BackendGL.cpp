#include "gfx/backend/opengl/BackendGL.hpp"

namespace gfx::gl 
{

Handle<Image>         BackendGL::createImage (ImageDesc& desc) 
{
    return {};
}

Handle<Buffer>        BackendGL::createBuffer(const BufferDesc& desc) 
{
    return buffers.Create(desc).Cast<Buffer>();
}

Handle<Mesh>          BackendGL::createMesh  (const MeshDesc& desc) 
{
    return meshes.Create(*this, desc).Cast<Mesh>();
}

Handle<ShaderDesc>    BackendGL::createShaderDesc() 
{
    return {};
}

Handle<PipelineState> BackendGL::createPipelineState() 
{
    return {};
}

Handle<PipelineDesc>  BackendGL::createPipelineDesc() 
{
    return {};
}

}