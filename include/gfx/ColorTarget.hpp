#pragma once

#include "gfx/Handle.hpp"
#include <cstdint>

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
    Handle<Image> image;
    BlendMode blend;
    bool writeColor = true;
    bool writeAlpha = true;
};

}