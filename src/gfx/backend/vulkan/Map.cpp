#include "gfx/backend/vulkan/Map.hpp"

#include <vulkan/vulkan.h>

namespace gfx::vk
{

uint32_t toVKFormat(ImageFormat format)
{
    switch (format)
    {
    case ImageFormat::R8_UNORM:            return VK_FORMAT_R8_UNORM;
    case ImageFormat::R8_SNORM:            return VK_FORMAT_R8_SNORM;
    case ImageFormat::R8_UINT:             return VK_FORMAT_R8_UINT;
    case ImageFormat::R8_SINT:             return VK_FORMAT_R8_SINT;

    case ImageFormat::RG8_UNORM:           return VK_FORMAT_R8G8_UNORM;
    case ImageFormat::RG8_SNORM:           return VK_FORMAT_R8G8_SNORM;
    case ImageFormat::RG8_UINT:            return VK_FORMAT_R8G8_UINT;
    case ImageFormat::RG8_SINT:            return VK_FORMAT_R8G8_SINT;

    case ImageFormat::RGBA8_UNORM:         return VK_FORMAT_R8G8B8A8_UNORM;
    case ImageFormat::RGBA8_SRGB:          return VK_FORMAT_R8G8B8A8_SRGB;
    case ImageFormat::RGBA8_SNORM:         return VK_FORMAT_R8G8B8A8_SNORM;
    case ImageFormat::RGBA8_UINT:          return VK_FORMAT_R8G8B8A8_UINT;
    case ImageFormat::RGBA8_SINT:          return VK_FORMAT_R8G8B8A8_SINT;

    case ImageFormat::BGRA8_UNORM:         return VK_FORMAT_B8G8R8A8_UNORM;
    case ImageFormat::BGRA8_SRGB:          return VK_FORMAT_B8G8R8A8_SRGB;

    case ImageFormat::R16_UNORM:           return VK_FORMAT_R16_UNORM;
    case ImageFormat::R16_UINT:            return VK_FORMAT_R16_UINT;
    case ImageFormat::R16_SINT:            return VK_FORMAT_R16_SINT;
    case ImageFormat::R16_SFLOAT:          return VK_FORMAT_R16_SFLOAT;

    case ImageFormat::RG16_UNORM:          return VK_FORMAT_R16G16_UNORM;
    case ImageFormat::RG16_UINT:           return VK_FORMAT_R16G16_UINT;
    case ImageFormat::RG16_SINT:           return VK_FORMAT_R16G16_SINT;
    case ImageFormat::RG16_SFLOAT:         return VK_FORMAT_R16G16_SFLOAT;

    case ImageFormat::RGBA16_UNORM:        return VK_FORMAT_R16G16B16A16_UNORM;
    case ImageFormat::RGBA16_UINT:         return VK_FORMAT_R16G16B16A16_UINT;
    case ImageFormat::RGBA16_SINT:         return VK_FORMAT_R16G16B16A16_SINT;
    case ImageFormat::RGBA16_SFLOAT:       return VK_FORMAT_R16G16B16A16_SFLOAT;

    case ImageFormat::R32_UINT:            return VK_FORMAT_R32_UINT;
    case ImageFormat::R32_SINT:            return VK_FORMAT_R32_SINT;
    case ImageFormat::R32_SFLOAT:          return VK_FORMAT_R32_SFLOAT;

    case ImageFormat::RG32_UINT:           return VK_FORMAT_R32G32_UINT;
    case ImageFormat::RG32_SINT:           return VK_FORMAT_R32G32_SINT;
    case ImageFormat::RG32_SFLOAT:         return VK_FORMAT_R32G32_SFLOAT;

    case ImageFormat::RGB32_SFLOAT:        return VK_FORMAT_R32G32B32_SFLOAT;

    case ImageFormat::RGBA32_UINT:         return VK_FORMAT_R32G32B32A32_UINT;
    case ImageFormat::RGBA32_SINT:         return VK_FORMAT_R32G32B32A32_SINT;
    case ImageFormat::RGBA32_SFLOAT:       return VK_FORMAT_R32G32B32A32_SFLOAT;

    case ImageFormat::RGB10A2_UNORM:       return VK_FORMAT_A2B10G10R10_UNORM_PACK32;
    case ImageFormat::RG11B10_UFLOAT:      return VK_FORMAT_B10G11R11_UFLOAT_PACK32;
    case ImageFormat::RGB9E5_UFLOAT:       return VK_FORMAT_E5B9G9R9_UFLOAT_PACK32;

    case ImageFormat::D16_UNORM:           return VK_FORMAT_D16_UNORM;
    case ImageFormat::D24_UNORM_S8_UINT:   return VK_FORMAT_D24_UNORM_S8_UINT;
    case ImageFormat::D32_SFLOAT:          return VK_FORMAT_D32_SFLOAT;
    case ImageFormat::D32_SFLOAT_S8_UINT:  return VK_FORMAT_D32_SFLOAT_S8_UINT;

    default:
        return VK_FORMAT_UNDEFINED;
    }
}

}
