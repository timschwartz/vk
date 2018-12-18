#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace vk
{
    class LogicalDevice;

    class PhysicalDevice
    {
      public:
        PhysicalDevice(VkPhysicalDevice device);
        ~PhysicalDevice();
        VkPhysicalDevice device = VK_NULL_HANDLE;

        void ShowExtensions();
        std::vector<VkExtensionProperties> GetExtensions();

        VkPhysicalDeviceFeatures GetFeatures();
        void ShowFeatures();

        VkPhysicalDeviceProperties GetProperties();
        void ShowProperties();
        std::vector<VkQueueFamilyProperties> GetQueueFamilyProperties();
        void ShowQueueFamilyProperties();

        LogicalDevice *GetLogicalDevice();
    };
}
