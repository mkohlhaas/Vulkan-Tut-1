#pragma once

#include <vulkan/vulkan.h>

extern VkCommandBuffer cmdBuffers[];

// Creates a command buffer.
void createCmdBuffers();

// Destroys command buffer.
void cleanCmdBuffer();
