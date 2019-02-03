#include <vulkan/vulkan.h>
#include <iostream>

int main() {
    uint32_t instanceLayersCount;
    vkEnumerateInstanceLayerProperties(&instanceLayersCount, nullptr);

    std::cout << "Nombre de layers disponibles: " << instanceLayersCount << std::endl;
    std::cin.get();
}