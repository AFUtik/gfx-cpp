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
    virtual void writeToImage(
        const uint8_t* pixels,
        uint32_t width,
        uint32_t height,
        uint32_t channels
    ) = 0;
    
    virtual void setImageFilter(ImageFilter filter) = 0;

    virtual ~Image() = default;
};

}