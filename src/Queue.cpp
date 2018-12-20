#include "vk.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cstring>

namespace vk
{
    Queue::Queue(VkQueue queue)
    {
        this->queue = queue;
    }

    Queue::~Queue()
    {
    }
}
