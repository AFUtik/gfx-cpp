#pragma once

#include "gfx/ResourceManager.hpp"
#include "gfx/IDevice.hpp"

#include "Buffer.hpp"
#include "Mesh.hpp"
#include "Image.hpp"

namespace gfx::gl 
{

struct BackendGL : public Device
{
    BackendGL();

    Handle<Image>         createImage (const ImageDesc& desc)  override;
    Handle<Buffer>        createBuffer(const BufferDesc& desc) override;

    Handle<MeshDesc>      meshDescHandle(const MeshDesc& desc) override;
    Handle<Mesh>          createMesh    (Handle<MeshDesc>& desc) override;

    Handle<ShaderDesc>    createShaderDesc() override;

    Handle<PipelineState> createPipelineState() override;
    Handle<PipelineDesc>  createPipelineDesc()  override;
private:
    ResourceManager<ImageGL>  images;

    ResourceManager<BufferGL> buffers;
    
    ResourceManager<MeshDescGL> meshDescs;
    ResourceManager<MeshGL>     meshes;
};

}