#pragma once

#include "macro.h"
#include <vulkan/vulkan.h>

extern VkCommandBuffer cmdBuffers[];
extern VkCommandPool cmdPool;

// Creates command pool and command buffers.
void createCmdBuffers();

// Destroys command buffers.
void destroyCmdBuffers();

// Begins single, one-time commands.
VkCommandBuffer beginSingleTimeCommands();

// Ends single, one-time commands.
void endSingleTimeCommands(VkCommandBuffer commandBuffer);
