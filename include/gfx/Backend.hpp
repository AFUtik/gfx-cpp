#pragma once

#include "IDevice.hpp"
#include "pch.hpp"

namespace gfx 
{

extern std::unique_ptr<Device> createOpenGLBackend();

}