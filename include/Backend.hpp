#pragma once

#include "IDevice.hpp"
#include <memory>

namespace gfx 
{

extern std::unique_ptr<Device> createOpenGLBackend();

}