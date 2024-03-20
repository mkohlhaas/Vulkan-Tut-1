#pragma once

#include <vulkan/vulkan_core.h>

extern VkBuffer indexBuffer;

// Creates vertex buffer.
void createIndexBuffer();

// Destroys vertex buffer.
void destroyIndexBuffer();
