#pragma once

#include <vulkan/vulkan.h>

extern VkCommandBuffer cmdBuffer;

// Creates a command buffer.
void createCmdBuffer();

// Destroys command buffer.
void cleanCmdBuffer();
