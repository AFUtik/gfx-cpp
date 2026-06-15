#pragma once

#include "gfx/IImage.hpp"

namespace gfx 
{

struct Image;

enum class BlendMode
{
    Opaque,
    Alpha,
    Additive,
    Multiply, 
    Screen, 
    None 
};

struct ColorTargetDesc
{   
    ImageFormat format;
    BlendMode blend;
    bool writeColor = true;
    bool writeAlpha = true;
    uint32_t width;
    uint32_t height;
};

struct DepthTargetDesc
{
    ImageFormat format;
    uint32_t width;
    uint32_t height;
};

}