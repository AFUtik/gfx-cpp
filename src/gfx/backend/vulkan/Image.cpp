#include "gfx/backend/vulkan/Image.hpp"
#include "gfx/backend/vulkan/Device.hpp"
#include "gfx/backend/vulkan/Buffer.hpp"
#include "gfx/backend/vulkan/Convert.hpp"

namespace gfx::vk {

int GetBytesPerTexFormat(VkFormat Format)
{
	switch (Format)
	{
	case VK_FORMAT_R8_SINT:
	case VK_FORMAT_R8_UNORM:
		return 1;
	case VK_FORMAT_R16_SFLOAT:
		return 2;
	case VK_FORMAT_R16G16_SFLOAT:
	case VK_FORMAT_R16G16_SNORM:
	case VK_FORMAT_B8G8R8A8_UNORM:
	case VK_FORMAT_R8G8B8A8_UNORM:
	case VK_FORMAT_R8G8B8A8_SNORM:	
	case VK_FORMAT_R8G8B8A8_SRGB:
		return 4;
	case VK_FORMAT_R16G16B16A16_SFLOAT:
		return 4 * sizeof(uint16_t);
	case VK_FORMAT_R32G32B32_SFLOAT:
		return 3 * sizeof(float);
	case VK_FORMAT_R8G8B8_SRGB:
		return 3;
	case VK_FORMAT_R32G32B32A32_SFLOAT:
		return 4 * sizeof(float);
	default:
		printf("Unknown format %d\n", Format);
		exit(1);
	}

	return 0;
}

SamplerVK::SamplerVK(DeviceVK& device, const SamplerDesc& desc) : device(device)
{
    VkFilter MinFilter;
    VkFilter MaxFilter;
    MinFilter = vk_convert::ToVK(desc.filter);
    MaxFilter = vk_convert::ToVK(desc.filter);
    VkSamplerAddressMode AddressMode = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    createTextureSampler(sampler, MinFilter, MaxFilter, AddressMode);
}

SamplerVK::~SamplerVK()
{
    if(!sampler) return;

    device.getDeletionQueue().push_function([sampler = this->sampler, device = this->device.device()] {
        vkDestroySampler(device, sampler, nullptr);
    });
}

void SamplerVK::createTextureSampler(VkSampler& sampler, VkFilter MinFilter, VkFilter MaxFilter, VkSamplerAddressMode AddressMode)
{
	VkSamplerCreateInfo SamplerInfo = {
		.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.magFilter = MinFilter,
		.minFilter = MaxFilter,
		.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
		.addressModeU = AddressMode,
		.addressModeV = AddressMode,
		.addressModeW = AddressMode,
		.mipLodBias = 0.0f,
		.anisotropyEnable = VK_FALSE,
		.maxAnisotropy = 1,
		.compareEnable = VK_FALSE,
		.compareOp = VK_COMPARE_OP_ALWAYS,
		.minLod = 0.0f,
		.maxLod = 0.0f,
		.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
		.unnormalizedCoordinates = VK_FALSE
	};
    if(vkCreateSampler(device.device(), &SamplerInfo, VK_NULL_HANDLE, &sampler) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create image sampler");
    } 
}

ImageVK::ImageVK(DeviceVK& device, VkImage vkImage, VkImageView vkImageView) :
    device(device),
    image(vkImage),
    view(vkImageView) {}

ImageVK::ImageVK(DeviceVK& device, const ImageDesc& desc) : 
    device(device),
    imageWidth(desc.width),
    imageHeight(desc.height),
    format(vk_convert::ToVk(desc.format))
{
    if(imageWidth!=0 && imageHeight!=0)
    {
        createImage();

        VkImageAspectFlags AspectFlags = VK_IMAGE_ASPECT_COLOR_BIT;
    	createImageView(AspectFlags);
    }
}

ImageVK::~ImageVK() {
    if(!vmaAllocation) return;

    struct DeletionInfo {
        VkImageView view;
        VkImage image;
        VmaAllocation allocation;
    };
    device.getDeletionQueue().push_function(
        [
            info = DeletionInfo{view, image, vmaAllocation}, 
            device = this->device.device(), 
            allocator = device.getVmaAllocator()]
        {
            vkDestroyImageView(device, info.view, nullptr);
            vmaDestroyImage(allocator, info.image, info.allocation);
        }
    );

}

void ImageVK::write(const uint8_t* pixels) 
{
	int LayerCount = isCubemap ? 6 : 1;
	updateTextureImage(LayerCount, pixels);
}

void ImageVK::setSampler(Handle<Sampler>& sampler)
{
    this->sampler = sampler.Cast<SamplerVK>();
}

void ImageVK::createImage()
{
	/*VkImageFormatProperties imageFormatProperties;
	vkGetPhysicalDeviceImageFormatProperties(m_physDevices.Selected().m_physDevice,
		TexFormat,
		VK_IMAGE_TYPE_2D,
		VK_IMAGE_TILING_OPTIMAL,
		UsageFlags,
		VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT,
		&imageFormatProperties);*/

	VkImageCreateInfo imageInfo = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		.pNext = NULL,
		.flags = isCubemap ? VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT : (VkImageCreateFlags)0,
		.imageType = VK_IMAGE_TYPE_2D,
		.format = format,
		.extent = VkExtent3D {.width = static_cast<uint32_t>(imageWidth), .height = static_cast<uint32_t>(imageHeight), .depth = 1 },
		.mipLevels = 1,
		.arrayLayers = isCubemap ? 6u : 1u,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.tiling = VK_IMAGE_TILING_OPTIMAL,
		.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = NULL,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
	};
    device.createImageWithInfo(imageInfo, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, image, vmaAllocation);
}

void ImageVK::updateTextureImage(int layerCount, const void* pPixels)
{
	int BytesPerPixel = GetBytesPerTexFormat(format);

	VkDeviceSize layerSize = imageWidth * imageHeight * BytesPerPixel;	 
	VkDeviceSize imageSize = layerCount * layerSize;

	BufferVK stagingBuffer(
		device,
		imageSize,
		1,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		VMA_MEMORY_USAGE_CPU_ONLY
	);
	stagingBuffer.map();
	stagingBuffer.write(pPixels, imageSize);
	stagingBuffer.unmap();

    VkCommandBuffer cmd = device.beginSingleTimeCommands();

    device.transitionImageLayout(image, format, imageLayout, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, layerCount);
	device.copyBufferToImage(stagingBuffer.getBuffer(), image, imageWidth, imageHeight, layerCount);
    device.transitionImageLayout(image, format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, layerCount);

    device.endSingleTimeCommands(cmd);

	imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
}

void ImageVK::createImageView(VkImageAspectFlags AspectFlags) 
{
	VkImageViewCreateInfo viewInfo =
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.image = image,
		.viewType = isCubemap ? VK_IMAGE_VIEW_TYPE_CUBE : VK_IMAGE_VIEW_TYPE_2D,
		.format = format,
		.subresourceRange = {
			.aspectMask = AspectFlags,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = isCubemap ? 6u : 1u
		}
	};

    int channels = GetBytesPerTexFormat(format);

	// Managing image view channels //
	if(channels == 4 || channels == 3) {
		viewInfo.components = {
			.r = VK_COMPONENT_SWIZZLE_IDENTITY,
			.g = VK_COMPONENT_SWIZZLE_IDENTITY,
			.b = VK_COMPONENT_SWIZZLE_IDENTITY,
			.a = VK_COMPONENT_SWIZZLE_IDENTITY
		};
	}
	else if(channels == 1) {
		viewInfo.components = {
			.r = VK_COMPONENT_SWIZZLE_ONE,
			.g = VK_COMPONENT_SWIZZLE_ONE,
			.b = VK_COMPONENT_SWIZZLE_ONE,
			.a = VK_COMPONENT_SWIZZLE_R
		};
	}
	else if(channels == 2) {
		viewInfo.components = {
			.r = VK_COMPONENT_SWIZZLE_R,
			.g = VK_COMPONENT_SWIZZLE_R,
			.b = VK_COMPONENT_SWIZZLE_R,
			.a = VK_COMPONENT_SWIZZLE_G
		};
	}

    if(vkCreateImageView(device.device(), &viewInfo, NULL, &view) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create image view");
    }
}

	#ifndef NDEBUG
    void ImageVK::addDebugInfo(const char* info)
	{
		device.addDebugObject(
			(uint64_t)image, 
			VK_OBJECT_TYPE_IMAGE, 
			vmaAllocation, 
			info, 
			this,
			imageWidth*imageHeight*GetBytesPerTexFormat(format)
		);
	}
	#endif

}
