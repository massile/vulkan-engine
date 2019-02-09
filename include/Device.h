#pragma once

#include <vulkan/vulkan.h>

namespace Vulkan {
    struct DeviceQueues {
        uint32_t familyIndex;
        uint32_t count;
    };

    extern VkPhysicalDevice PhysicalGpu;
    extern VkDevice LogicalGpu;
    extern DeviceQueues DeviceQueue;
    extern VkPhysicalDeviceMemoryProperties MemoryProperties;

    VkResult QueryFirstAvailableGpu(VkInstance& instance);
    void FetchPhysicalGpuStats(VkPhysicalDevice &physicalDevice);

    VkResult CreateLogicalGpu(VkPhysicalDevice &physicalDevice, VkPhysicalDeviceFeatures* usedFeatures = nullptr);
}