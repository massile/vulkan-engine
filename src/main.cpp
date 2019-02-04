#include "Device.h"

int main() {
    Api::PrintInstanceLayerProperties();

    VkInstance instance = Api::CreateInstance();
    VkPhysicalDevice gpu = Api::FetchFirstPhysicalDevice(instance);
    VkDevice device = Api::CreateLogicalDevice(gpu);
}