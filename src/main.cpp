#include <vulkan/vulkan.h>
#include "Instance.h"
#include "Device.h"

int main() {
    // CHECK(PrintInstanceLayerNames());

    std::vector<const char*> instanceLayers = {
        "VK_LAYER_LUNARG_standard_validation",
    };
    CHECK(Vulkan::CreateInstance("Engine", instanceLayers));
    CHECK(Vulkan::QueryFirstAvailableGpu(Vulkan::Instance));
    Vulkan::FetchPhysicalGpuStats(Vulkan::PhysicalGpu);
    CHECK(Vulkan::CreateLogicalGpu(Vulkan::PhysicalGpu));
}