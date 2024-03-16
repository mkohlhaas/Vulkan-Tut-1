#pragma once

#include <vulkan/vulkan.h>

extern VkCommandPool cmdPool;
extern VkCommandBuffer cmdBuffer;

void createCommandPool();
void allocateCommandBuffer();
