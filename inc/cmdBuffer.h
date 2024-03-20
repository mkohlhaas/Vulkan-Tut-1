#pragma once

#include <vulkan/vulkan.h>

extern VkCommandBuffer cmdBuffers[];
extern VkCommandPool cmdPool;

// Creates command pool and command buffers.
void createCmdBuffers();

// Destroys command buffers.
void destroyCmdBuffers();
