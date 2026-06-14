#pragma once

#include <cstdint>

#include "Handle.hpp"

namespace gfx 
{

enum BackendType
{
    OpenGL,
    Vulkan
};

struct Shader;
struct Buffer;
struct Mesh;
struct Image;

struct PipelineDesc;
struct PipelineState;

struct ShaderDesc;
struct BufferDesc;
struct MeshDesc;
struct ImageDesc;

struct Device
{
    Device(BackendType type) : type(type) {};

    virtual Handle<Image>         createImage (const ImageDesc& desc)  = 0;
    virtual Handle<Buffer>        createBuffer(const BufferDesc& desc) = 0;

    virtual Handle<MeshDesc>      meshDescHandle(const MeshDesc& desc)   = 0;
    virtual Handle<Mesh>          createMesh    (Handle<MeshDesc>& desc) = 0;

    virtual Handle<ShaderDesc>    createShaderDesc() = 0;

    virtual Handle<PipelineState> createPipelineState() = 0;
    virtual Handle<PipelineDesc>  createPipelineDesc()  = 0;

    virtual ~Device() = default;

    inline BackendType getBackendType() const {return type;}
private:
    BackendType type;
};

}