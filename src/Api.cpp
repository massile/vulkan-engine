#include <cassert>
#include <iostream>
#include "Api.h"

namespace Api {
    void PrintInstanceLayerProperties() {
        uint32_t instanceLayerCount;
        // When the second parameter is null, it returns the layer count
        vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);

        // First, all the instance layers are fetched
        std::vector<VkLayerProperties> layerProperties(instanceLayerCount);
        vkEnumerateInstanceLayerProperties(&instanceLayerCount, layerProperties.data());

        for (VkLayerProperties &layerProperty : layerProperties) {
            uint32_t instanceExtensionCount;
            vkEnumerateInstanceExtensionProperties(layerProperty.layerName, &instanceExtensionCount, nullptr);

            // Then we fetch all the extensions available in each layer
            std::vector<VkExtensionProperties> instanceExtensions(instanceExtensionCount);
            vkEnumerateInstanceExtensionProperties(layerProperty.layerName, &instanceExtensionCount,
                                                   instanceExtensions.data());

            for (VkExtensionProperties &extensionProperties : instanceExtensions) {
                std::cout << "Layer: " << layerProperty.layerName << std::endl;
                std::cout << "Extension: " << extensionProperties.extensionName << std::endl;
            }
        }
    }

    VkInstance CreateInstance() {
        VkInstance instance;
        // These layers are activated for debugging
        const char *layerNames[] = {
                "VK_LAYER_LUNARG_standard_validation",
                "VK_LAYER_LUNARG_object_tracker"
        };
        // These extensions are required to display something on the screen
        const char *extensionNames[] = {
                VK_KHR_SURFACE_EXTENSION_NAME,
                VK_KHR_WIN32_SURFACE_EXTENSION_NAME
        };

        // Appends some information about the current engine / app we are about to create
        VkApplicationInfo applicationInfo = {};
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
        applicationInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
        applicationInfo.pEngineName = "Vulkan Engine";  // TODO: Find a name for the engine
        applicationInfo.pApplicationName = "Game"; // TODO: Find a name for the app

        // Creates the instance
        VkInstanceCreateInfo instanceInfo = {};
        instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceInfo.enabledLayerCount = 1;
        instanceInfo.enabledExtensionCount = 2;
        instanceInfo.pApplicationInfo = &applicationInfo;
        instanceInfo.ppEnabledExtensionNames = extensionNames;
        instanceInfo.ppEnabledLayerNames = layerNames;

        VkResult result = vkCreateInstance(&instanceInfo, nullptr, &instance);

        assert(result == VK_SUCCESS);
        return instance;
    }

    VkPhysicalDevice FetchFirstPhysicalDevice(const VkInstance &instance) {
        uint32_t GPUCount;
        vkEnumeratePhysicalDevices(instance, &GPUCount, nullptr);

        std::vector<VkPhysicalDevice> GPUs(GPUCount);
        VkResult result = vkEnumeratePhysicalDevices(instance, &GPUCount, GPUs.data());

        assert(result == VK_SUCCESS && GPUCount > 0);
        return GPUs[0];
    }

    uint32_t FetchFirstGraphicsFamilyIndex(const VkPhysicalDevice &gpu) {
        uint32_t familyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(gpu, &familyCount, nullptr);

        std::vector<VkQueueFamilyProperties> familyProperties(familyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(gpu, &familyCount, familyProperties.data());

        uint32_t graphicsFamilyIndex = 0;
        for (uint32_t i = 0; i < familyCount; i++) {
            VkQueueFamilyProperties &familyProperty = familyProperties[i];

            // This family supports graphics calculation
            if ((familyProperty.queueFlags & VK_QUEUE_GRAPHICS_BIT) == VK_QUEUE_GRAPHICS_BIT) {
                graphicsFamilyIndex = i;
                std::cout << "Chosen family index: " << i << std::endl;
                std::cout << "Queue count in this family: " << familyProperty.queueCount << std::endl;
                break;
            }
        }

        return graphicsFamilyIndex;
    }

    VkDevice CreateLogicalDevice(const VkPhysicalDevice &gpu) {
        // To understand what a queue is please refer to
        // https://github.com/massile/vulkan-engine/blob/master/docs/jargon_overview.md#vocabulary
        uint32_t familyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(gpu, &familyCount, nullptr);

        std::vector<VkQueueFamilyProperties> familyProperties(familyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(gpu, &familyCount, familyProperties.data());

        const float queuePriorities[] = {0.0f};
        // Create one queue for the logical device
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = queuePriorities;
        queueCreateInfo.queueFamilyIndex = FetchFirstGraphicsFamilyIndex(gpu);

        // This extension is required to use the WSI swapchain
        const char *extensionNames[] = {"VK_KHR_swapchain"};

        // Create the logical device
        VkDeviceCreateInfo logicalDeviceInfo = {};
        logicalDeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        logicalDeviceInfo.enabledExtensionCount = 1;
        logicalDeviceInfo.queueCreateInfoCount = 1;
        logicalDeviceInfo.ppEnabledExtensionNames = extensionNames;
        logicalDeviceInfo.pQueueCreateInfos = &queueCreateInfo;

        VkDevice device;
        VkResult result = vkCreateDevice(gpu, &logicalDeviceInfo, nullptr, &device);
        assert(result == VK_SUCCESS);

        return device;
    }
}

