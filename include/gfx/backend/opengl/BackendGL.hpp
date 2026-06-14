#pragma once

#include "gfx/IShader.hpp"
#include "gfx/ResourceManager.hpp"
#include "gfx/IDevice.hpp"

#include "gfx/PipelineState.hpp"


#include "Buffer.hpp"
#include "Mesh.hpp"
#include "Image.hpp"
#include "Shader.hpp"
#include "RenderPass.hpp"

#include "PipelineLayout.hpp"
#include "RenderPipeline.hpp"

namespace gfx::gl 
{

struct BackendGL : public Device
{
    BackendGL();

    Handle<Image>         createImage (const ImageDesc& desc)  override;
    Handle<Buffer>        createBuffer(const BufferDesc& desc) override;

    Handle<MeshDesc>      meshDescHandle(const MeshDesc& desc) override;
    Handle<Mesh>          createMesh    (Handle<MeshDesc>& desc) override;

    Handle<Shader>        createShader(const ShaderDesc& desc) override;

    RenderPass*            createScreenRenderPass(const RenderPassDesc& desc) override;
    Handle<RenderPass>     createRenderPass      (const RenderPassDesc& desc) override;
    Handle<PipelineState>  createPipelineState   ()  override;
    Handle<PipelineLayout> createPipelineLayout  (const PipelineLayoutDesc& desc) override;
    Handle<RenderPipeline> createRenderPipeline  (const RenderPipelineDesc& desc) override;
private:
    std::unique_ptr<ScreenRenderPassGL> screenRenderPass;

    ResourceManager<ImageGL>       images;
    ResourceManager<BufferGL>      buffers;
    ResourceManager<MeshDescGL>    meshDescs;
    ResourceManager<MeshGL>        meshes;

    ResourceManager<ShaderGL>      shaders;
    ResourceManager<RenderPassGL>  renderPasses;

    // Big structures, block size was decreased
    ResourceManager<PipelineState,  64>   pipelineStates; 
    ResourceManager<PipelineLayoutGL, 64> pipelineLayouts;
    ResourceManager<RenderPipelineGL, 64> renderPipelines;
};

}