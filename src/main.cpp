#include <iostream>
#include "../config.h"
#include "vk.h"

int main(int argc, char *argv[])
{
    vk::Instance *spock = new vk::Instance(PACKAGE_STRING, "none");

    spock->RequireExtension("VK_KHR_surface");
    spock->Create();

    vk::PhysicalDevice *physicalDevice = nullptr;
    try
    {
        physicalDevice = spock->GetPhysicalDevice("AMD Radeon (TM) R9 390 Series");
    }
    catch(std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
        exit(1);
    }

    physicalDevice->ShowQueueFamilyProperties();
//    std::cout << "Physical device extensions:" << std::endl;
//    physicalDevice->ShowExtensions();

    vk::LogicalDevice *logicalDevice = nullptr;
    logicalDevice = physicalDevice->GetLogicalDevice();
    logicalDevice->RequireExtension("VK_KHR_swapchain");
    logicalDevice->Create();

    VkQueue gq = logicalDevice->GetGraphicsQueue();
    return 0;
}
