#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace vk
{
    class Queue
    {
      public:
        Queue(VkQueue);
        ~Queue();
        void Create();
      private:
        VkQueue queue = {};
    };
}
