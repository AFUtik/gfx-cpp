#include "gfx/backend/opengl/BackendGL.hpp"
#include "gfx/Handle.hpp"
#include "gfx/RenderPass.hpp"
#include "gfx/backend/opengl/Mesh.hpp"
#include "gfx/backend/opengl/RenderPass.hpp"
#include "gfx/backend/opengl/RenderPipeline.hpp"

#include "gfx/PipelineLayout.hpp"
#include "gfx/RenderPipeline.hpp"

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

Handle<Shader>        BackendGL::createShader(const ShaderDesc& desc) 
{
    return shaders.Create(desc);
}

RenderPass*        BackendGL::createScreenRenderPass(const RenderPassDesc& desc)
{
    screenRenderPass = std::make_unique<ScreenRenderPassGL>(desc);
    return static_cast<RenderPass*>(screenRenderPass.get());
}

Handle<RenderPass> BackendGL::createRenderPass      (const RenderPassDesc& desc)
{
    return renderPasses.Create(desc);
}

// Pipeline 
Handle<PipelineState> BackendGL::createPipelineState() 
{
    return pipelineStates.Create();
}

Handle<PipelineLayout> BackendGL::createPipelineLayout(const PipelineLayoutDesc& desc)
{
    return pipelineLayouts.Create(desc);
}

Handle<RenderPipeline> BackendGL::createRenderPipeline(const RenderPipelineDesc& desc) 
{
    return renderPipelines.Create(desc);
}

}