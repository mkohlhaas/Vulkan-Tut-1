#pragma once

#include <vulkan/vulkan_core.h>

// Create buffer with appropriate usage and property requirements.
// Returns `buffer` and `memory`.
void createBuffer(VkDeviceSize, VkBufferUsageFlags, VkMemoryPropertyFlags, VkBuffer *buffer, VkDeviceMemory *memory);

// Copies buffer `srcBuffer` to `dstBuffer`.
void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

// Destroys buffer and its bound memory.
void destroyBuffer(VkBuffer buffer, VkDeviceMemory memory);

// Finds memory based on usage and properties.
uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
