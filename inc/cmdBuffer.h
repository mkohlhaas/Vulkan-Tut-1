#pragma once

#include <vulkan/vulkan.h>

extern VkCommandBuffer cmdBuffers[];

// Creates command buffers.
void createCmdBuffers();

// Destroys command buffers.
void destroyCmdBuffers();
