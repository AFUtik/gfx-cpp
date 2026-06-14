#include "gfx/backend/opengl/RenderPipeline.hpp"

#include <glad/glad.h>

namespace gfx::gl 
{

RenderPipelineGL::RenderPipelineGL(const RenderPipelineDesc& desc)
{
    program = glCreateProgram();
    
}

}