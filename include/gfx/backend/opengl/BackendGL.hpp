#pragma once

#include "gfx/ResourceManager.hpp"
#include "gfx/IDevice.hpp"

#include "Buffer.hpp"
#include "Mesh.hpp"

namespace gfx::gl 
{

struct BackendGL : Device
{
    Handle<Image>         createImage (ImageDesc& desc)  override;
    Handle<Buffer>        createBuffer(const BufferDesc& desc) override;
    Handle<Mesh>          createMesh  (const MeshDesc& desc)   override;

    Handle<ShaderDesc>    createShaderDesc() override;

    Handle<PipelineState> createPipelineState() override;
    Handle<PipelineDesc>  createPipelineDesc()  override;
private:
    ResourceManager<BufferGL> buffers;
    ResourceManager<MeshGL>   meshes;
};

}