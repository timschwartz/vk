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
        void ShowExtensions();
        std::vector<VkExtensionProperties> GetExtensions();
        VkPhysicalDeviceFeatures GetFeatures();
        void ShowFeatures();
        VkPhysicalDeviceProperties GetProperties();
        void ShowProperties();
        std::vector<VkQueueFamilyProperties> GetQueueFamilyProperties();
        void ShowQueueFamilyProperties();
        LogicalDevice *GetLogicalDevice();
        VkPhysicalDevice device = VK_NULL_HANDLE;
    };
}
