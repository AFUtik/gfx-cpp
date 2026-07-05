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
    BlendMode blend;
    bool writeColor = true;
    bool writeAlpha = true;
    ImageDesc imageDesc;
};

}
