#include "vk.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cstring>
    
namespace vk
{
    Instance::Instance(std::string appName, std::string engineName)
    {
        this->appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        this->appInfo.pApplicationName = appName.c_str();
        this->appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        this->appInfo.pEngineName = engineName.c_str();
        this->appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        this->appInfo.apiVersion = VK_API_VERSION_1_0;
    
        return;
    }
    
    void Instance::Create()
    {
        for(auto &re : this->requiredExtensions)
        {
            bool available = false;
            for(auto &ae : this->GetExtensions(nullptr))
            {
                if(strcmp(ae.extensionName, re) == 0) available = true;
            }
    
            if(!available)
            {
                std::string message = std::string("Required extension ") + re + " not available.";
                throw std::runtime_error(message);
            }
        }
    
        this->createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        this->createInfo.pApplicationInfo = &this->appInfo;
        this->createInfo.ppEnabledExtensionNames = &this->requiredExtensions[0];
        this->createInfo.enabledExtensionCount = this->requiredExtensions.size();
        this->createInfo.ppEnabledLayerNames = &this->requiredLayers[0];
        this->createInfo.enabledLayerCount = this->requiredLayers.size();
    
        if(vkCreateInstance(&this->createInfo, nullptr, &this->instance) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create Vulkan instance!");
        }
    }
    
    void Instance::RequireExtension(const char *extension)
    {
        this->requiredExtensions.push_back(extension);
    }
    
    std::vector<VkExtensionProperties> Instance::GetExtensions(const char *pLayerName)
    {
        uint32_t extensionCount = 0;
        std::vector<VkExtensionProperties> extensions;
        vkEnumerateInstanceExtensionProperties(pLayerName, &extensionCount, nullptr);
        extensions.resize(extensionCount);
        vkEnumerateInstanceExtensionProperties(pLayerName, &extensionCount, extensions.data());
        return extensions;
    }
    
    void Instance::ShowExtensions()
    {
        this->ShowExtensions(nullptr);
    }
    
    void Instance::ShowExtensions(const char *pLayerName)
    {
        if(this->createInfo.enabledExtensionCount == 0)
        {
            std::vector<VkExtensionProperties> extensions = this->GetExtensions(pLayerName);
            std::cout << extensions.size() << " extensions available:" << std::endl;
      
            for (const auto &extension : extensions)
            {
                std::cout << "\t" << extension.extensionName << " version " << extension.specVersion << std::endl;
            }
    
            std::cout << "No extensions enabled." << std::endl;
            return;
        }
    
        std::cout << this->createInfo.enabledExtensionCount << " extensions enabled:" << std::endl;
    
        uint32_t counter = 0;
        while(counter < this->createInfo.enabledExtensionCount)
        {
            std::cout << "\t" << this->createInfo.ppEnabledExtensionNames[counter] << std::endl;
            counter++;
        }
    }
    
    void Instance::RequireLayer(const char *layer)
    {
        this->requiredLayers.push_back(layer);
    }
    
    std::vector<VkLayerProperties> Instance::GetLayers()
    {
        uint32_t layerCount = 0;
        std::vector<VkLayerProperties> layers;
    
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        layers.resize(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, layers.data());
        return layers;
    }
    
    void Instance::ShowLayers()
    {
        if(this->createInfo.enabledLayerCount == 0)
        {
            std::vector<VkLayerProperties> layers = this->GetLayers();
    
            std::cout << layers.size() << " layers available:" << std::endl;
    
            for(const auto &layer : layers)
            {
                std::cout << "\t" << layer.layerName << std::endl;
            }
            return;
        }
    
        std::cout << this->createInfo.enabledLayerCount << " layers enabled:" << std::endl;
    
        uint32_t counter = 0;
        while(counter < this->createInfo.enabledLayerCount)
        {
            std::cout << "\t" << this->createInfo.ppEnabledLayerNames[counter] << std::endl;
            counter++;
        }
    }
    
    void Instance::ShowPhysicalDevices()
    {
        std::vector<VkPhysicalDevice> devices = this->GetPhysicalDevices();
        std::cout << devices.size() << " physical devices:" << std::endl;
    
        for(auto &d : devices)
        {
            VkPhysicalDeviceProperties properties;
            vkGetPhysicalDeviceProperties(d, &properties);
    
            std::cout << "\t" << properties.deviceName << std::endl;
    
            vk::PhysicalDevice pd(d);
            for(auto &e : pd.GetExtensions())
            {
            //    std::cout << "\t\t" << e.extensionName << std::endl;
            }
        }
    }
    
    std::vector<VkPhysicalDevice> Instance::GetPhysicalDevices()
    {
        if(this->instance == nullptr)
            throw std::runtime_error("Must create Vulkan instance first.");
    
        uint32_t device_count = 0;
        std::vector<VkPhysicalDevice> devices;
        vkEnumeratePhysicalDevices(this->instance, &device_count, nullptr);
        devices.resize(device_count);
        vkEnumeratePhysicalDevices(this->instance, &device_count, devices.data());
        return devices;
    }

    PhysicalDevice *Instance::GetPhysicalDevice(const char *deviceName)
    {
        for(auto &d : this->GetPhysicalDevices())
        {
            VkPhysicalDeviceProperties properties;
            vkGetPhysicalDeviceProperties(d, &properties);

            if(strcmp(properties.deviceName, deviceName) == 0)
                return new PhysicalDevice(d);
        }

        std::string message = std::string("Requested physical device ") + deviceName + " not found.";
        throw std::runtime_error(message);
    }
    
    Instance::~Instance()
    {
        vkDestroyInstance(this->instance, nullptr);
    }
}
