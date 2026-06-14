#include "gfx/backend/opengl/BackendGL.hpp"
#include "gfx/backend/opengl/Mesh.hpp"

namespace gfx::gl 
{

BackendGL::BackendGL() : Device(BackendType::OpenGL)
{

}

Handle<Image>         BackendGL::createImage (const ImageDesc& desc) 
{
    return images.Create(desc).Cast<Image>();
}

Handle<Buffer>        BackendGL::createBuffer(const BufferDesc& desc) 
{
    return buffers.Create(desc).Cast<Buffer>();
}

Handle<MeshDesc>      BackendGL::meshDescHandle(const MeshDesc& desc)
{
    return meshDescs.Create(desc);
}

Handle<Mesh>          BackendGL::createMesh  (Handle<MeshDesc>& desc) 
{
    return meshes.Create(*this, desc.Cast<MeshDescGL>()).Cast<Mesh>();
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