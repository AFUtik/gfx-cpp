#include "gfx/backend/vulkan/Shader.hpp"
#include "gfx/backend/vulkan/Device.hpp"
#include "gfx/backend/vulkan/Convert.hpp"

namespace gfx::vk 
{


ShaderVK::ShaderVK(DeviceVK& device, const ShaderDesc& desc) : device(device), shaderStage(vk_convert::ToVk(desc.stage))
{
    if(desc.spirv_size == 0)
    {
        throw std::runtime_error("Shader's spirv is empty.");
    }

    VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = desc.spirv_size;
	createInfo.pCode    = desc.spirv;

	if (vkCreateShaderModule(device.device(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module");
	}
}

ShaderVK::~ShaderVK()
{
    device.getDeletionQueue().push_function([shaderModule = this->shaderModule, device = this->device.device()] {
        vkDestroyShaderModule(device, shaderModule, nullptr); 
    });
}

}
