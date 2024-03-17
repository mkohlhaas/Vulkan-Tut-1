#pragma once

#include <vulkan/vulkan.h>

extern VkCommandBuffer cmdBuffer;

void createCommandPool();
void allocateCommandBuffer();
void cleanCmdPool();
