#pragma once

#include "gfx/Handle.hpp"

#include "pch.hpp"

namespace gfx 
{

enum class ImageFormat
{
    // 8-bit
    R8_UNORM,
    R8_SNORM,
    R8_UINT,
    R8_SINT,

    RG8_UNORM,
    RG8_SNORM,
    RG8_UINT,
    RG8_SINT,

    RGBA8_UNORM,
    RGBA8_SRGB,
    RGBA8_SNORM,
    RGBA8_UINT,
    RGBA8_SINT,

    BGRA8_UNORM,
    BGRA8_SRGB,

    // 16-bit
    R16_UNORM,
    R16_UINT,
    R16_SINT,
    R16_SFLOAT,

    RG16_UNORM,
    RG16_UINT,
    RG16_SINT,
    RG16_SFLOAT,

    RGBA16_UNORM,
    RGBA16_UINT,
    RGBA16_SINT,
    RGBA16_SFLOAT,

    // 32-bit
    R32_UINT,
    R32_SINT,
    R32_SFLOAT,

    RG32_UINT,
    RG32_SINT,
    RG32_SFLOAT,

    RGB32_SFLOAT,

    RGBA32_UINT,
    RGBA32_SINT,
    RGBA32_SFLOAT,

    // Packed
    RGB10A2_UNORM,
    RG11B10_UFLOAT,
    RGB9E5_UFLOAT,

    // Depth / Stencil
    D16_UNORM,
    D24_UNORM_S8_UINT,
    D32_SFLOAT,
    D32_SFLOAT_S8_UINT,

    Undefined
};

enum ImageFilter
{
    LINEAR,
    NEAREST,
    LINEAR_MIPMAP,
    NEAREST_MIPMAP
};

enum class ImageUsage : uint32_t
{
    ColorAttachment = 1 << 0,
    DepthStencil    = 1 << 1,
    Sampled         = 1 << 2,
    TransferSrc     = 1 << 3,
    TransferDst     = 1 << 4,
};


struct SamplerDesc
{
    ImageFilter filter;
};

struct Sampler 
{

};

struct Image
{
    virtual void write(const uint8_t* data) = 0;
    virtual void setSampler(Handle<Sampler>& sampler) = 0;

    virtual ~Image() = default;
};

struct ImageDesc
{
    uint32_t    width    = 0;
    uint32_t    height   = 0; 
    ImageFormat format;
};

}
