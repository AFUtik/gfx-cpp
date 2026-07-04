#include "gfx/backend/vulkan/BackendVK.hpp"

namespace gfx::vk 
{

BackendVK::BackendVK(Window* windowInstance) : 
    Device(BackendType::Vulkan), 
    window(windowInstance), 
    device(window),
    renderer(device, window)
{
    std::cout << "Backend successfully initialized." << std::endl;
}

BackendVK::~BackendVK()
{
    
}

}
