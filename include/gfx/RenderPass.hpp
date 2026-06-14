#pragma once

#include "Handle.hpp"

#include <vector>
#include <glm/glm.hpp>

namespace gfx 
{

struct Image;
struct ColorTarget;

struct RenderPass
{
    virtual void begin() = 0;
    virtual void end()   = 0;
protected:
    glm::vec4 clearColor;
};

struct RenderPassDesc
{
    std::vector<Handle<ColorTarget>> colorTargets;
    Handle<Image>                    depthTarget;

    glm::vec4 clearColor;
};

}