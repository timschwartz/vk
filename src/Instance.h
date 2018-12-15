#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace vk
{
    class PhysicalDevice;

    class Instance
    {
      public:
        Instance(std::string appName, std::string engineName);
        ~Instance();
        void ShowExtensions(const char *);
        void ShowExtensions();
        void RequireExtension(const char *);
        void ShowLayers();
        void RequireLayer(const char *);
        void Create();
        void ShowPhysicalDevices();
        PhysicalDevice *GetPhysicalDevice(const char *); 
      private:
        VkApplicationInfo appInfo = {};
        VkInstanceCreateInfo createInfo = {};
        VkInstance instance = VK_NULL_HANDLE;
        std::vector<VkExtensionProperties> GetExtensions(const char *);
        std::vector<char const *> requiredExtensions = {};
        std::vector<VkLayerProperties> GetLayers();
        std::vector<char const *> requiredLayers = {};
        std::vector<VkPhysicalDevice> GetPhysicalDevices();
    };
}
