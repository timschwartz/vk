#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace vk
{
    class PhysicalDevice;

    class LogicalDevice
    {
      public:
        LogicalDevice(PhysicalDevice *physicalDevice);
        ~LogicalDevice();
        void RequireExtension(const char *);
        void RequireFeatures(VkPhysicalDeviceFeatures);
        void Create();
        VkQueue GetGraphicsQueue();
      private:
        PhysicalDevice *physicalDevice = nullptr;
        VkDevice device = {};
        std::vector<const char *> requiredExtensions = {};
        VkPhysicalDeviceFeatures requiredFeatures = {};
        VkQueue graphicsQueue = VK_NULL_HANDLE;
    };
}
