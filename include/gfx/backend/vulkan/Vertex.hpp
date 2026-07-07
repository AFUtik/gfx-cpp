#pragma once

#include "gfx/Vertex.hpp"
#include "Convert.hpp"

#include "pch.hpp"

#include <vulkan/vulkan.h>

namespace gfx::vk 
{

inline std::vector<VkVertexInputBindingDescription> getBindingDescriptions(const VertexLayout& layout) {
	std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);

	bindingDescriptions[0].binding   = 0;
	bindingDescriptions[0].stride    = layout.stride;
	bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	return bindingDescriptions;
}

inline std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions(const VertexLayout& layout) {
	std::vector<VkVertexInputAttributeDescription> attributeDescriptions;
    for(const VertexAttribute& attr : layout.attributes)
    { 
        VkVertexInputAttributeDescription desc;
        desc.binding  = attr.binding;
        desc.location = attr.location;
        desc.format   = vk_convert::ToVk(attr.format);
        desc.offset   = attr.offset;
        attributeDescriptions.push_back(desc);
    }
	return attributeDescriptions;
}

}
