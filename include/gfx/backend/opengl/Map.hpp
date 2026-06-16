#pragma once

#include "gfx/IBuffer.hpp"
#include "gfx/IShader.hpp"
#include "gfx/ColorTarget.hpp"
#include "gfx/PipelineState.hpp"

namespace gfx::gl 
{

extern uint32_t toGLBufferType  (BufferType type);
extern uint32_t toGLUnsignedType(uint64_t size); 
extern uint32_t toGLShaderType  (ShaderStage stage);
extern uint32_t bufferUsageHint (BufferUsage usage, BufferAccess access);
extern void     applyBlendMode  (BlendMode mode);


extern uint32_t toGLTopology(PrimitiveTopology t);
extern uint32_t toGLBlendOp(BlendOp op);
extern uint32_t toGLBlendFactor(BlendFactor f);
extern uint32_t toGLCompare(CompareOp op);

}