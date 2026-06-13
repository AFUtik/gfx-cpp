#pragma once

#include <cstdint>

#include <glm/glm.hpp>
#include <vector>

namespace gfx
{

enum class VertexFormat
{
    Float1,
    Float2,
    Float3,
    Float4,
    Half2,
    Half4,
    UInt1,  UInt2, UInt4,
    UNorm2,
    UNorm4,
    SNorm4,
    A2B10G10R10_UNorm
};

struct VertexAttribute
{
    uint32_t     location = 0; 
    uint32_t     binding  = 0;
    VertexFormat format   = VertexFormat::Float3;
    uint32_t     offset   = 0;
};

struct VertexLayout
{
    std::vector<VertexAttribute> attributes;
    uint32_t stride = 0;
};

struct Vertex
{
    glm::vec3 pos;

    inline constexpr static VertexLayout getLayout()
    {
        return VertexLayout{
            {{0, 0, VertexFormat::Float3, offsetof(Vertex, pos)},},
            sizeof(Vertex)
        };
    }
};

}