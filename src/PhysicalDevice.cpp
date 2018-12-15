#include "vk.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cstring>

namespace vk
{
    PhysicalDevice::PhysicalDevice(VkPhysicalDevice device)
    {
        this->device = device;
    }

    std::vector<VkExtensionProperties> PhysicalDevice::GetExtensions()
    {
        uint32_t count = 0;
        std::vector<VkExtensionProperties> properties;
    
        vkEnumerateDeviceExtensionProperties(this->device, nullptr, &count, nullptr);
        properties.resize(count);
        vkEnumerateDeviceExtensionProperties(this->device, nullptr, &count, &properties[0]);
        return properties;
    }

    void PhysicalDevice::ShowExtensions()
    {
        for(auto &e : this->GetExtensions())
        {
            std::cout << e.extensionName << std::endl;
        }
    }

    VkPhysicalDeviceFeatures PhysicalDevice::GetFeatures()
    {
        VkPhysicalDeviceFeatures features = {};

        vkGetPhysicalDeviceFeatures(this->device, &features);
        return features;
    }

    void PhysicalDevice::ShowFeatures()
    {
        VkPhysicalDeviceFeatures features = this->GetFeatures();
    }

    VkPhysicalDeviceProperties PhysicalDevice::GetProperties()
    {
        VkPhysicalDeviceProperties properties = {};

        vkGetPhysicalDeviceProperties(this->device, &properties);
        return properties;
    }

    void PhysicalDevice::ShowProperties()
    {
        VkPhysicalDeviceProperties properties = this->GetProperties();
    }
    
    std::vector<VkQueueFamilyProperties> PhysicalDevice::GetQueueFamilyProperties()
    {
        uint32_t count = 0;
        std::vector<VkQueueFamilyProperties> properties = {};
        
        vkGetPhysicalDeviceQueueFamilyProperties(this->device, &count, nullptr);
        properties.resize(count);
        vkGetPhysicalDeviceQueueFamilyProperties(this->device, &count, &properties[0]);
        return properties;
    }

    void PhysicalDevice::ShowQueueFamilyProperties()
    {
        for(auto &p : this->GetQueueFamilyProperties())
        {
            std::cout << "Queue Family:" << std::endl;
            if(p.queueFlags && VK_QUEUE_GRAPHICS_BIT) std::cout << "\tGraphics" << std::endl;
            if(p.queueFlags && VK_QUEUE_COMPUTE_BIT) std::cout << "\tCompute" << std::endl;
            if(p.queueFlags && VK_QUEUE_TRANSFER_BIT) std::cout << "\tTransfer" << std::endl;
            if(p.queueFlags && VK_QUEUE_SPARSE_BINDING_BIT) std::cout << "\tSparse binding" << std::endl;
            if(p.queueFlags && VK_QUEUE_PROTECTED_BIT) std::cout << "\tProtected" << std::endl;
            std::cout << "\n\t" << p.queueCount << " queues in this family.\n" << std::endl;
        }
    }

    LogicalDevice *PhysicalDevice::GetLogicalDevice()
    {
        return new LogicalDevice(this);
    }

    PhysicalDevice::~PhysicalDevice()
    {
    }
}
