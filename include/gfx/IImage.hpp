#pragma once

#include <cstdint>

namespace gfx 
{

enum ImageFilter
{
    LINEAR,
    NEAREST,
    LINEAR_MIPMAP,
    NEAREST_MIPMAP
};

struct Image
{
    virtual void bind() = 0;

    virtual void write(const uint8_t* data) = 0;
    virtual void setImageFilter(ImageFilter filter)  = 0;

    virtual ~Image() = default;
};

struct ImageDesc
{
    uint32_t    width;
    uint32_t    height; 
    uint32_t    channels;
    ImageFilter filter;
};

}