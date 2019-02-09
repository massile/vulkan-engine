#include <iostream>
#include <Device.h>

namespace Vulkan {
    VkPhysicalDevice PhysicalGpu;
    VkDevice LogicalGpu;
    DeviceQueues DeviceQueue;
    VkPhysicalDeviceMemoryProperties MemoryProperties;

    VkResult QueryFirstAvailableGpu(VkInstance &instance) {
        uint32_t availableDevicesCount;
        vkEnumeratePhysicalDevices(instance, &availableDevicesCount, nullptr);

        auto *physicalDevices = new VkPhysicalDevice[availableDevicesCount];
        VkResult result = vkEnumeratePhysicalDevices(instance, &availableDevicesCount, physicalDevices);

        PhysicalGpu = physicalDevices[0];
        return result;
    }

    void FetchPhysicalGpuStats(VkPhysicalDevice &physicalDevice) {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(physicalDevice, &properties);

        uint32_t apiVer = properties.apiVersion;
        std::cout << "GPU name:                    " << properties.deviceName << std::endl;
        std::cout << "GPU type:                    " << properties.deviceType << std::endl;
        std::cout << "GPU api version:             " << VK_VERSION_MAJOR(apiVer) << "." << VK_VERSION_MINOR(apiVer) << "." << VK_VERSION_PATCH(apiVer) << std::endl;
        std::cout << "GPU driver version:          " << properties.driverVersion << std::endl;
        std::cout << "Queue priorities:            " << properties.limits.discreteQueuePriorities << std::endl;

        VkPhysicalDeviceFeatures features;
        vkGetPhysicalDeviceFeatures(physicalDevice, &features);

        std::cout << "Geometry shader support:     " << features.geometryShader << std::endl;
        std::cout << "Tessellation shader support: " << features.tessellationShader << std::endl;

        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &MemoryProperties);

        uint32_t queueFamiliesCount;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamiliesCount, nullptr);
        auto *queueFamilyProperties = new VkQueueFamilyProperties[queueFamiliesCount];
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamiliesCount, queueFamilyProperties);

        std::cout << "Queue families count:        " << queueFamiliesCount << std::endl;
        for (uint32_t i = 0; i < queueFamiliesCount; i++) {
            bool supportsGraphics = ((queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0);
            if (supportsGraphics) {
                DeviceQueue.familyIndex = i;
                DeviceQueue.count = queueFamilyProperties[i].queueCount;
            }
            std::cout << std::endl << "Queue family #" << i << std::endl;
            std::cout << "Queue count:             " << queueFamilyProperties[i].queueCount << std::endl;
            std::cout << "Supports graphics:       " << supportsGraphics << std::endl;
            std::cout << "Supports computing:      " << ((queueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) != 0) << std::endl;
            std::cout << "Supports transfer:       " << ((queueFamilyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT) != 0) << std::endl;
            std::cout << "Supports sparse binding: " << ((queueFamilyProperties[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) != 0) << std::endl;
        }

        delete[] queueFamilyProperties;
    }

    VkResult CreateLogicalGpu(VkPhysicalDevice &physicalDevice, VkPhysicalDeviceFeatures* usedFeatures) {
        VkDeviceQueueCreateInfo queueCreateInfo;
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.pNext = nullptr;
        queueCreateInfo.flags = 0;
        queueCreateInfo.queueFamilyIndex = DeviceQueue.familyIndex;
        queueCreateInfo.queueCount = DeviceQueue.count;
        queueCreateInfo.pQueuePriorities = new float[DeviceQueue.count] { 1.0f };

        VkDeviceCreateInfo deviceCreateInfo;
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pNext = nullptr;
        deviceCreateInfo.flags = 0;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
        deviceCreateInfo.enabledLayerCount = 0;
        deviceCreateInfo.ppEnabledLayerNames = nullptr;
        deviceCreateInfo.enabledExtensionCount = 0;
        deviceCreateInfo.ppEnabledExtensionNames = nullptr;
        deviceCreateInfo.pEnabledFeatures = usedFeatures;

        return vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &LogicalGpu);
    }
}