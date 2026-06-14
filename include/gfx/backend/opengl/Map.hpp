#pragma once

#include "gfx/IBuffer.hpp"

#include <cstdint>

namespace gfx::gl 
{

extern uint32_t toGLBufferType  (BufferType type);
extern uint32_t toGLUnsignedType(uint64_t size); 
extern uint32_t bufferUsageHint (BufferUsage usage, BufferAccess access);

}