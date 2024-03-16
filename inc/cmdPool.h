#pragma once

#include <vulkan/vulkan.h>

extern VkCommandPool commandPool;
extern VkCommandBuffer commandBuffer;

void createCommandPool();
void allocateCommandBuffer();
