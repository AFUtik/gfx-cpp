#include "Backend.hpp"
#include "backend/opengl/BackendGL.hpp"

namespace gfx
{

std::unique_ptr<Device> createOpenGLBackend()
{
    return std::make_unique<gl::BackendGL>();
}

}