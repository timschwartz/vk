#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace vk
{
    class PhysicalDevice;
    class Queue;

    class LogicalDevice
    {
      public:
        LogicalDevice(PhysicalDevice *physicalDevice);
        ~LogicalDevice();
        void RequireExtension(const char *);
        void RequireFeatures(VkPhysicalDeviceFeatures);
        void Create();
        Queue *GetQueue(uint32_t, uint32_t);
        Queue *GetGraphicsQueue();
      private:
        PhysicalDevice *physicalDevice = nullptr;
        VkDevice device = {};
        std::vector<const char *> requiredExtensions = {};
        VkPhysicalDeviceFeatures requiredFeatures = {};
    };
}
