#include "vk.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cstring>

namespace vk
{
    LogicalDevice::LogicalDevice(PhysicalDevice *physicalDevice)
    {
        this->physicalDevice = physicalDevice;
    }

    void LogicalDevice::RequireExtension(const char *extension)
    {
        this->requiredExtensions.push_back(extension);
    }

    void LogicalDevice::RequireFeatures(VkPhysicalDeviceFeatures features)
    {
        this->requiredFeatures = features;
    }

    void LogicalDevice::Create()
    {
        for(auto &re : this->requiredExtensions)
        {
            bool available = false;

            for(auto &ae : this->physicalDevice->GetExtensions())
            {
                if(strcmp(re, ae.extensionName) == 0) available = true;
            }

            if(!available)
            {
                std::string message = std::string("LogicalDevice::Create() Physical device does not have requested extension: ") + re;
                throw std::runtime_error(message);
            }
        }

        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = 0;
        queueCreateInfo.queueCount = 1;
        float queuePriority = 1.0f;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        VkDeviceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = &queueCreateInfo;
        createInfo.queueCreateInfoCount = 1;
        createInfo.pEnabledFeatures = &this->requiredFeatures;
        createInfo.enabledExtensionCount = this->requiredExtensions.size();
        createInfo.ppEnabledExtensionNames = this->requiredExtensions.data();
        createInfo.enabledLayerCount = 0;

        if(vkCreateDevice(this->physicalDevice->device, &createInfo, nullptr, &this->device) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create logical device!");
        }
    }

    VkQueue LogicalDevice::GetGraphicsQueue()
    {
        if(this->graphicsQueue == VK_NULL_HANDLE)
        {
            vkGetDeviceQueue(this->device, 0, 0, &this->graphicsQueue);
            if(this->graphicsQueue == VK_NULL_HANDLE)
                throw std::runtime_error("LogicalDevice::GetGraphicsQueue() Couldn't get graphics queue.");
        }
        return this->graphicsQueue;
    }

    LogicalDevice::~LogicalDevice()
    {
        vkDestroyDevice(this->device, nullptr);
    }
}
