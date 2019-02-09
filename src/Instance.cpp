#include <iostream>
#include "Instance.h"

namespace Vulkan {
    VkInstance Instance;

    VkResult CreateInstance(const char *appName, const std::vector<const char*>& validationLayers) {
        VkApplicationInfo applicationInfo;
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pNext = nullptr;
        applicationInfo.pApplicationName = appName;
        applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
        applicationInfo.pEngineName = "Ultimate Vulkan engine";
        applicationInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
        applicationInfo.apiVersion = VK_API_VERSION_1_1;

        VkInstanceCreateInfo instanceCreateInfo;
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pNext = nullptr;
        instanceCreateInfo.flags = 0;
        instanceCreateInfo.pApplicationInfo = &applicationInfo;
        instanceCreateInfo.enabledLayerCount = validationLayers.size();
        instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
        instanceCreateInfo.enabledExtensionCount = 0;
        instanceCreateInfo.ppEnabledExtensionNames = nullptr;

        return vkCreateInstance(&instanceCreateInfo, nullptr, &Vulkan::Instance);
    }

    VkResult PrintInstanceLayerNames() {
        uint32_t layersCount;
        vkEnumerateInstanceLayerProperties(&layersCount, nullptr);
        auto *layerProperties = new VkLayerProperties[layersCount];
        VkResult result = vkEnumerateInstanceLayerProperties(&layersCount, layerProperties);

        std::cout << "Instance layers count: " << layersCount << std::endl;
        for (int i = 0; i < layersCount; i++) {
            std::cout << "Name:        " << layerProperties[i].layerName << std::endl;
            std::cout << "Description: " << layerProperties[i].description << std::endl << std::endl;
        }

        return result;
    }
}