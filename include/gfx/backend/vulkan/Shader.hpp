#pragma once

#include "gfx/IShader.hpp"

struct VkShaderModule_T;
using VkShaderModule = VkShaderModule_T*;

namespace gfx::vk 
{

struct DeviceVK;

struct ShaderVK : public Shader
{
    ShaderVK(DeviceVK& device, const ShaderDesc& desc);
    ~ShaderVK();

    inline VkShaderModule getShaderModule() {return shaderModule;}
private:
    DeviceVK& device;

    VkShaderModule shaderModule;
    uint32_t       shaderStage;
};

}
