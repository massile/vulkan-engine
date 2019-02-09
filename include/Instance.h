#pragma once

#include <cassert>
#include <vector>
#include <vulkan/vulkan.h>
#define CHECK(val) assert(val == VK_SUCCESS)

namespace Vulkan {
    extern VkInstance Instance;
    VkResult CreateInstance(const char* appName, const std::vector<const char*>& validationLayers);
    VkResult PrintInstanceLayerNames();
}