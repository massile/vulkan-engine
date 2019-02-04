#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace Api {
    /**
     * Vulkan first communicates with the loader and locates the driver.
     * The driver exposes a number of extensions and layers available on the GPU.
     * Each layer may contain multiple extensions;
     * This function displays the instance layers and its extensions in the console.
     */
    void PrintInstanceLayerProperties();

    /**
     * Creates the Vulkan instance.
     * It initializes the communication with the hardware and enables the required layers.
     *
     * (https://github.com/massile/vulkan-engine/blob/master/docs/jargon_overview.md#hardware-initialization)
     */
    VkInstance CreateInstance();

    /**
     * Fetches information about the first physical device (GPU) available on the existing system
     */
    VkPhysicalDevice FetchFirstPhysicalDevice(const VkInstance &instance);

    /**
     * Information about queue families is required for the logical device to be created.
     * For now, just one queue family will be created on the logical device.
     * This function returns the index of the first family that supports graphics calculation.
     */
    uint32_t FetchFirstGraphicsFamilyIndex(const VkPhysicalDevice &gpu);

    /**
     * Creates a logical device (a software abstraction of the GPU) out of the physical one.
     */
    VkDevice CreateLogicalDevice(const VkPhysicalDevice &gpu);
}