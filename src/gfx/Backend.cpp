#include "gfx/Backend.hpp"
//#include "gfx/backend/opengl/BackendGL.hpp"
#include "gfx/backend/vulkan/BackendVK.hpp"

namespace gfx
{

/*
std::unique_ptr<Device> createOpenGLBackend(Window* windowInstance)
{
    return std::make_unique<gl::BackendGL>(windowInstance);
}
*/

std::unique_ptr<Device> createVulkanBackend(Window* windowInstance)
{
    return std::make_unique<vk::BackendVK>(windowInstance);
}

}
