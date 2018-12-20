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

        // TODO: don't hardcode totalQueueCreateInfos
        //       don't hardcode queueFamilyIndex
        //       don't hardcode queueCount 
        uint32_t totalQueueCreateInfos = 1, counter = 0;

        VkDeviceQueueCreateInfo queueCreateInfo[totalQueueCreateInfos] = {};

        while(counter < totalQueueCreateInfos)
        {
            queueCreateInfo[counter].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo[counter].queueFamilyIndex = 0;
            queueCreateInfo[counter].queueCount = 1;
            float queuePriority = 1.0f;
            queueCreateInfo[counter].pQueuePriorities = &queuePriority;
            counter++;
        }

        VkDeviceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = &queueCreateInfo[0];
        createInfo.queueCreateInfoCount = totalQueueCreateInfos;
        createInfo.pEnabledFeatures = &this->requiredFeatures;
        createInfo.enabledExtensionCount = this->requiredExtensions.size();
        createInfo.ppEnabledExtensionNames = this->requiredExtensions.data();
        createInfo.enabledLayerCount = 0;

        if(vkCreateDevice(this->physicalDevice->device, &createInfo, nullptr, &this->device) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create logical device!");
        }
    }

    Queue *LogicalDevice::GetGraphicsQueue()
    {
        // TODO: Don't hardcode these values. They happen to work on my video card.
        return this->GetQueue(0, 0);
    }

    Queue *LogicalDevice::GetQueue(uint32_t queueFamilyIndex, uint32_t queueIndex)
    {
        VkQueue queue;
        vkGetDeviceQueue(this->device, queueFamilyIndex, queueIndex, &queue);

        if(queue == VK_NULL_HANDLE)
            throw std::runtime_error("LogicalDevice::GetQueue() couldn't get queue.");
        return new Queue(queue);
    }

    LogicalDevice::~LogicalDevice()
    {
        vkDestroyDevice(this->device, nullptr);
    }
}
