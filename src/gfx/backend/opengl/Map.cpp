#include "gfx/backend/opengl/Map.hpp"

#include <glad/glad.h>

namespace gfx::gl 
{

GLenum toGLShaderType(ShaderStage stage)
{
    switch (stage)
    {
        case ShaderStage::Vertex:         return GL_VERTEX_SHADER;
        case ShaderStage::Fragment:       return GL_FRAGMENT_SHADER;
        case ShaderStage::Geometry:       return GL_GEOMETRY_SHADER;
        case ShaderStage::TessControl:    return GL_TESS_CONTROL_SHADER;
        case ShaderStage::TessEvaluation: return GL_TESS_EVALUATION_SHADER;
        case ShaderStage::Compute:        return GL_COMPUTE_SHADER;
        default:                          return 0;
    }
}

uint32_t toGLUnsignedType(uint64_t size)
{
    switch (size) 
    {
        case 1: return GL_UNSIGNED_BYTE;
        case 2: return GL_UNSIGNED_SHORT;
        case 4: return GL_UNSIGNED_INT;
        default: return 0;
    }
}

uint32_t toGLBufferType(BufferType type)
{
    switch (type)
    {
        case BufferType::Vertex:  return GL_ARRAY_BUFFER;
        case BufferType::Index:   return GL_ELEMENT_ARRAY_BUFFER;
        case BufferType::Uniform: return GL_UNIFORM_BUFFER;
        case BufferType::Storage: return GL_SHADER_STORAGE_BUFFER;
        case BufferType::Staging: return GL_ARRAY_BUFFER;
    }
    return GL_ARRAY_BUFFER;
}

uint32_t bufferUsageHint(BufferUsage usage, BufferAccess access)
{
    if (access == BufferAccess::GPUOnly)
        return GL_STATIC_DRAW;

    if (access == BufferAccess::CPUToGPU)
        return (usage == BufferUsage::Dynamic)
            ? GL_DYNAMIC_DRAW
            : GL_STREAM_DRAW;

    return GL_DYNAMIC_READ; // GPU → CPU
}

uint32_t toGLTopology(PrimitiveTopology t)
{
    switch (t)
    {
        case PrimitiveTopology::TriangleList: return GL_TRIANGLES;
        case PrimitiveTopology::TriangleStrip: return GL_TRIANGLE_STRIP;
        case PrimitiveTopology::LineList: return GL_LINES;
        case PrimitiveTopology::LineStrip: return GL_LINE_STRIP;
        case PrimitiveTopology::PointList: return GL_POINTS;
    }
    return GL_TRIANGLES;
}

uint32_t toGLBlendFactor(BlendFactor f)
{
    switch (f)
    {
        case BlendFactor::Zero: return GL_ZERO;
        case BlendFactor::One: return GL_ONE;
        case BlendFactor::SrcColor: return GL_SRC_COLOR;
        case BlendFactor::OneMinusSrcColor: return GL_ONE_MINUS_SRC_COLOR;
        case BlendFactor::DstColor: return GL_DST_COLOR;
        case BlendFactor::OneMinusDstColor: return GL_ONE_MINUS_DST_COLOR;
        case BlendFactor::SrcAlpha: return GL_SRC_ALPHA;
        case BlendFactor::OneMinusSrcAlpha: return GL_ONE_MINUS_SRC_ALPHA;
    }
    return GL_ONE;
}

uint32_t toGLBlendOp(BlendOp op)
{
    switch (op)
    {
        case BlendOp::Add: return GL_FUNC_ADD;
        case BlendOp::Subtract: return GL_FUNC_SUBTRACT;
        case BlendOp::ReverseSubtract: return GL_FUNC_REVERSE_SUBTRACT;
        case BlendOp::Min: return GL_MIN;
        case BlendOp::Max: return GL_MAX;
    }
    return GL_FUNC_ADD;
}

uint32_t toGLCompare(CompareOp op)
{
    switch (op)
    {
        case CompareOp::Never:        return GL_NEVER;
        case CompareOp::Less:         return GL_LESS;
        case CompareOp::Equal:        return GL_EQUAL;
        case CompareOp::LessOrEqual:  return GL_LEQUAL;
        case CompareOp::Greater:      return GL_GREATER;
        case CompareOp::Always:       return GL_ALWAYS;
    }
    return GL_LESS;
}

}