#pragma once

#include "gfx/PipelineState.hpp"
#include "gfx/IImage.hpp"
#include "gfx/Vertex.hpp"

#include <vulkan/vulkan.h>

namespace gfx::vk_convert
{

inline VkIndexType ToIndexTypeVk(uint32_t stride)
{
    
    switch (stride) 
    {
        case 4: return VK_INDEX_TYPE_UINT32;
        case 2: return VK_INDEX_TYPE_UINT16;
        case 1: return VK_INDEX_TYPE_UINT8;
    }
    return VK_INDEX_TYPE_UINT32;
}

inline VkFormat ToVk(VertexFormat format)
{
    switch (format)
    {
        case VertexFormat::Float1:             return VK_FORMAT_R32_SFLOAT;
        case VertexFormat::Float2:             return VK_FORMAT_R32G32_SFLOAT;
        case VertexFormat::Float3:             return VK_FORMAT_R32G32B32_SFLOAT;
        case VertexFormat::Float4:             return VK_FORMAT_R32G32B32A32_SFLOAT;

        case VertexFormat::Half2:              return VK_FORMAT_R16G16_SFLOAT;
        case VertexFormat::Half4:              return VK_FORMAT_R16G16B16A16_SFLOAT;

        case VertexFormat::UInt1:              return VK_FORMAT_R32_UINT;
        case VertexFormat::UInt2:              return VK_FORMAT_R32G32_UINT;
        case VertexFormat::UInt4:              return VK_FORMAT_R32G32B32A32_UINT;

        case VertexFormat::UNorm2:             return VK_FORMAT_R8G8_UNORM;
        case VertexFormat::UNorm4:             return VK_FORMAT_R8G8B8A8_UNORM;
        case VertexFormat::SNorm4:             return VK_FORMAT_R8G8B8A8_SNORM;

        case VertexFormat::A2B10G10R10_UNorm:  return VK_FORMAT_A2B10G10R10_UNORM_PACK32;
    }

    return VK_FORMAT_UNDEFINED;
}
inline VkFormat ToVk(ImageFormat f)
{ 
    switch (f)
    {
        case ImageFormat::R8_UNORM:            return VK_FORMAT_R8_UNORM;
        case ImageFormat::R8_SNORM:            return VK_FORMAT_R8_SNORM;
        case ImageFormat::R8_UINT:             return VK_FORMAT_R8_UINT;
        case ImageFormat::R8_SINT:             return VK_FORMAT_R8_SINT;

        case ImageFormat::RG8_UNORM:           return VK_FORMAT_R8G8_UNORM;
        case ImageFormat::RG8_SNORM:           return VK_FORMAT_R8G8_SNORM;
        case ImageFormat::RG8_UINT:            return VK_FORMAT_R8G8_UINT;
        case ImageFormat::RG8_SINT:            return VK_FORMAT_R8G8_SINT;

        case ImageFormat::RGBA8_UNORM:         return VK_FORMAT_R8G8B8A8_UNORM;
        case ImageFormat::RGBA8_SRGB:          return VK_FORMAT_R8G8B8A8_SRGB;
        case ImageFormat::RGBA8_SNORM:         return VK_FORMAT_R8G8B8A8_SNORM;
        case ImageFormat::RGBA8_UINT:          return VK_FORMAT_R8G8B8A8_UINT;
        case ImageFormat::RGBA8_SINT:          return VK_FORMAT_R8G8B8A8_SINT;

        case ImageFormat::BGRA8_UNORM:         return VK_FORMAT_B8G8R8A8_UNORM;
        case ImageFormat::BGRA8_SRGB:          return VK_FORMAT_B8G8R8A8_SRGB;

        case ImageFormat::R16_UNORM:           return VK_FORMAT_R16_UNORM;
        case ImageFormat::R16_UINT:            return VK_FORMAT_R16_UINT;
        case ImageFormat::R16_SINT:            return VK_FORMAT_R16_SINT;
        case ImageFormat::R16_SFLOAT:          return VK_FORMAT_R16_SFLOAT;

        case ImageFormat::RG16_UNORM:          return VK_FORMAT_R16G16_UNORM;
        case ImageFormat::RG16_UINT:           return VK_FORMAT_R16G16_UINT;
        case ImageFormat::RG16_SINT:           return VK_FORMAT_R16G16_SINT;
        case ImageFormat::RG16_SFLOAT:         return VK_FORMAT_R16G16_SFLOAT;

        case ImageFormat::RGBA16_UNORM:        return VK_FORMAT_R16G16B16A16_UNORM;
        case ImageFormat::RGBA16_UINT:         return VK_FORMAT_R16G16B16A16_UINT;
        case ImageFormat::RGBA16_SINT:         return VK_FORMAT_R16G16B16A16_SINT;
        case ImageFormat::RGBA16_SFLOAT:       return VK_FORMAT_R16G16B16A16_SFLOAT;

        case ImageFormat::R32_UINT:            return VK_FORMAT_R32_UINT;
        case ImageFormat::R32_SINT:            return VK_FORMAT_R32_SINT;
        case ImageFormat::R32_SFLOAT:          return VK_FORMAT_R32_SFLOAT;

        case ImageFormat::RG32_UINT:           return VK_FORMAT_R32G32_UINT;
        case ImageFormat::RG32_SINT:           return VK_FORMAT_R32G32_SINT;
        case ImageFormat::RG32_SFLOAT:         return VK_FORMAT_R32G32_SFLOAT;

        case ImageFormat::RGB32_SFLOAT:        return VK_FORMAT_R32G32B32_SFLOAT;

        case ImageFormat::RGBA32_UINT:         return VK_FORMAT_R32G32B32A32_UINT;
        case ImageFormat::RGBA32_SINT:         return VK_FORMAT_R32G32B32A32_SINT;
        case ImageFormat::RGBA32_SFLOAT:       return VK_FORMAT_R32G32B32A32_SFLOAT;

        case ImageFormat::RGB10A2_UNORM:       return VK_FORMAT_A2B10G10R10_UNORM_PACK32;
        case ImageFormat::RG11B10_UFLOAT:      return VK_FORMAT_B10G11R11_UFLOAT_PACK32;
        case ImageFormat::RGB9E5_UFLOAT:       return VK_FORMAT_E5B9G9R9_UFLOAT_PACK32;

        case ImageFormat::D16_UNORM:           return VK_FORMAT_D16_UNORM;
        case ImageFormat::D24_UNORM_S8_UINT:   return VK_FORMAT_D24_UNORM_S8_UINT;
        case ImageFormat::D32_SFLOAT:          return VK_FORMAT_D32_SFLOAT;
        case ImageFormat::D32_SFLOAT_S8_UINT:  return VK_FORMAT_D32_SFLOAT_S8_UINT;

        default: return VK_FORMAT_UNDEFINED;
    }
}

inline VkFilter ToVK(ImageFilter f)
{
    switch (f)
    {
        case ImageFilter::NEAREST: return VK_FILTER_NEAREST;
        case ImageFilter::LINEAR:  return VK_FILTER_LINEAR;
        defualt: {}
    }
    return VK_FILTER_LINEAR;
}

inline VkShaderStageFlagBits ToVk(ShaderStage s)
{
    switch (s)
    {
        case ShaderStage::Vertex:         return VK_SHADER_STAGE_VERTEX_BIT;
        case ShaderStage::Fragment:       return VK_SHADER_STAGE_FRAGMENT_BIT;
        case ShaderStage::Geometry:       return VK_SHADER_STAGE_GEOMETRY_BIT;
        case ShaderStage::TessControl:    return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
        case ShaderStage::TessEvaluation: return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
        case ShaderStage::Compute:        return VK_SHADER_STAGE_COMPUTE_BIT;

        default: throw std::runtime_error("Unknown shader stage");
    }
}

inline VkPrimitiveTopology ToVk(PrimitiveTopology t)
{
    switch (t)
    {
        case PrimitiveTopology::PointList:                return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
        case PrimitiveTopology::LineList:                 return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
        case PrimitiveTopology::LineStrip:                return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
        case PrimitiveTopology::TriangleList:             return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        case PrimitiveTopology::TriangleStrip:            return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
        case PrimitiveTopology::TriangleFan:              return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
        case PrimitiveTopology::LineListAdjacency:        return VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
        case PrimitiveTopology::LineStripAdjacency:       return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;
        case PrimitiveTopology::TriangleListAdjacency:    return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY;
        case PrimitiveTopology::TriangleStripAdjacency:   return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
        case PrimitiveTopology::PatchList:                return VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
    }
    assert(false && "Unknown PrimitiveTopology");
    return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
}

// ---------- Blend ----------
inline VkBlendFactor ToVk(BlendFactor f)
{
    switch (f)
    {
        case BlendFactor::Zero:                  return VK_BLEND_FACTOR_ZERO;
        case BlendFactor::One:                   return VK_BLEND_FACTOR_ONE;
        case BlendFactor::SrcColor:              return VK_BLEND_FACTOR_SRC_COLOR;
        case BlendFactor::OneMinusSrcColor:      return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
        case BlendFactor::DstColor:              return VK_BLEND_FACTOR_DST_COLOR;
        case BlendFactor::OneMinusDstColor:      return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
        case BlendFactor::SrcAlpha:              return VK_BLEND_FACTOR_SRC_ALPHA;
        case BlendFactor::OneMinusSrcAlpha:      return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        case BlendFactor::DstAlpha:              return VK_BLEND_FACTOR_DST_ALPHA;
        case BlendFactor::OneMinusDstAlpha:      return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
        case BlendFactor::ConstantColor:         return VK_BLEND_FACTOR_CONSTANT_COLOR;
        case BlendFactor::OneMinusConstantColor: return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
        case BlendFactor::ConstantAlpha:         return VK_BLEND_FACTOR_CONSTANT_ALPHA;
        case BlendFactor::OneMinusConstantAlpha: return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA;
        case BlendFactor::SrcAlphaSaturate:      return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
        case BlendFactor::Src1Color:             return VK_BLEND_FACTOR_SRC1_COLOR;
        case BlendFactor::OneMinusSrc1Color:     return VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
        case BlendFactor::Src1Alpha:             return VK_BLEND_FACTOR_SRC1_ALPHA;
        case BlendFactor::OneMinusSrc1Alpha:     return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
    }
    assert(false && "Unknown BlendFactor");
    return VK_BLEND_FACTOR_ONE;
}

inline VkBlendOp ToVk(BlendOp op)
{
    switch (op)
    {
        case BlendOp::Add:             return VK_BLEND_OP_ADD;
        case BlendOp::Subtract:        return VK_BLEND_OP_SUBTRACT;
        case BlendOp::ReverseSubtract: return VK_BLEND_OP_REVERSE_SUBTRACT;
        case BlendOp::Min:             return VK_BLEND_OP_MIN;
        case BlendOp::Max:             return VK_BLEND_OP_MAX;
    }
    assert(false && "Unknown BlendOp");
    return VK_BLEND_OP_ADD;
}

inline VkLogicOp ToVk(LogicOp op)
{
    switch (op)
    {
        case LogicOp::Clear:        return VK_LOGIC_OP_CLEAR;
        case LogicOp::Set:          return VK_LOGIC_OP_SET;
        case LogicOp::Copy:         return VK_LOGIC_OP_COPY;
        case LogicOp::CopyInverted: return VK_LOGIC_OP_COPY_INVERTED;
        case LogicOp::NoOp:         return VK_LOGIC_OP_NO_OP;
        case LogicOp::Invert:       return VK_LOGIC_OP_INVERT;
        case LogicOp::And:          return VK_LOGIC_OP_AND;
        case LogicOp::Nand:         return VK_LOGIC_OP_NAND;
        case LogicOp::Or:           return VK_LOGIC_OP_OR;
        case LogicOp::Nor:          return VK_LOGIC_OP_NOR;
        case LogicOp::Xor:          return VK_LOGIC_OP_XOR;
        case LogicOp::Equivalent:   return VK_LOGIC_OP_EQUIVALENT;
        case LogicOp::AndReverse:   return VK_LOGIC_OP_AND_REVERSE;
        case LogicOp::AndInverted:  return VK_LOGIC_OP_AND_INVERTED;
        case LogicOp::OrReverse:    return VK_LOGIC_OP_OR_REVERSE;
        case LogicOp::OrInverted:   return VK_LOGIC_OP_OR_INVERTED;
    }
    assert(false && "Unknown LogicOp");
    return VK_LOGIC_OP_COPY;
}

inline VkColorComponentFlags ToVk(ColorWriteMask mask)
{
    VkColorComponentFlags flags = 0;
    auto m = static_cast<uint8_t>(mask);
    if (m & static_cast<uint8_t>(ColorWriteMask::R)) flags |= VK_COLOR_COMPONENT_R_BIT;
    if (m & static_cast<uint8_t>(ColorWriteMask::G)) flags |= VK_COLOR_COMPONENT_G_BIT;
    if (m & static_cast<uint8_t>(ColorWriteMask::B)) flags |= VK_COLOR_COMPONENT_B_BIT;
    if (m & static_cast<uint8_t>(ColorWriteMask::A)) flags |= VK_COLOR_COMPONENT_A_BIT;
    return flags;
}

inline VkCompareOp ToVk(CompareOp op)
{
    switch (op)
    {
        case CompareOp::Never:        return VK_COMPARE_OP_NEVER;
        case CompareOp::Less:         return VK_COMPARE_OP_LESS;
        case CompareOp::Equal:        return VK_COMPARE_OP_EQUAL;
        case CompareOp::LessOrEqual:  return VK_COMPARE_OP_LESS_OR_EQUAL;
        case CompareOp::Greater:      return VK_COMPARE_OP_GREATER;
        case CompareOp::Always:       return VK_COMPARE_OP_ALWAYS;
    }
    assert(false && "Unknown CompareOp");
    return VK_COMPARE_OP_LESS;
}

inline VkStencilOp ToVk(StencilOp op)
{
    switch (op)
    {
        case StencilOp::Keep:            return VK_STENCIL_OP_KEEP;
        case StencilOp::Zero:            return VK_STENCIL_OP_ZERO;
        case StencilOp::Replace:         return VK_STENCIL_OP_REPLACE;
        case StencilOp::IncrementClamp:  return VK_STENCIL_OP_INCREMENT_AND_CLAMP;
        case StencilOp::DecrementClamp:  return VK_STENCIL_OP_DECREMENT_AND_CLAMP;
        case StencilOp::Invert:          return VK_STENCIL_OP_INVERT;
        case StencilOp::IncrementWrap:   return VK_STENCIL_OP_INCREMENT_AND_WRAP;
        case StencilOp::DecrementWrap:   return VK_STENCIL_OP_DECREMENT_AND_WRAP;
    }
    assert(false && "Unknown StencilOp");
    return VK_STENCIL_OP_KEEP;
}

inline VkStencilOpState ToVk(const StencilOpState& s)
{
    VkStencilOpState out{};
    out.failOp      = ToVk(s.failOp);
    out.passOp      = ToVk(s.passOp);
    out.depthFailOp = ToVk(s.depthFailOp);
    out.compareOp   = ToVk(s.compareOp);
    out.compareMask = s.compareMask;
    out.writeMask   = s.writeMask;
    out.reference   = s.reference;
    return out;
}

inline VkCullModeFlags ToVk(CullMode c)
{
    switch (c)
    {
        case CullMode::None:  return VK_CULL_MODE_NONE;
        case CullMode::Front: return VK_CULL_MODE_FRONT_BIT;
        case CullMode::Back:  return VK_CULL_MODE_BACK_BIT;
    }
    assert(false && "Unknown CullMode");
    return VK_CULL_MODE_NONE;
}

inline VkPolygonMode ToVk(FillMode f)
{
    switch (f)
    {
        case FillMode::Fill: return VK_POLYGON_MODE_FILL;
        case FillMode::Line: return VK_POLYGON_MODE_LINE;
    }
    assert(false && "Unknown FillMode");
    return VK_POLYGON_MODE_FILL;
}

inline VkFrontFace ToVk(FrontFace f)
{
    switch (f)
    {
        case FrontFace::Clockwise:        return VK_FRONT_FACE_CLOCKWISE;
        case FrontFace::CounterClockwise: return VK_FRONT_FACE_COUNTER_CLOCKWISE;
    }
    assert(false && "Unknown FrontFace");
    return VK_FRONT_FACE_COUNTER_CLOCKWISE;
}

inline VkSampleCountFlagBits ToVk(SampleCount s)
{
    switch (s)
    {
        case SampleCount::x1:  return VK_SAMPLE_COUNT_1_BIT;
        case SampleCount::x2:  return VK_SAMPLE_COUNT_2_BIT;
        case SampleCount::x4:  return VK_SAMPLE_COUNT_4_BIT;
        case SampleCount::x8:  return VK_SAMPLE_COUNT_8_BIT;
        case SampleCount::x16: return VK_SAMPLE_COUNT_16_BIT;
    }
    assert(false && "Unknown SampleCount");
    return VK_SAMPLE_COUNT_1_BIT;
}

} // namespace gfx::vk_convert
