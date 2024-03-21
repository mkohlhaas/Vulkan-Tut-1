#pragma once

#include <bits/stdint-uintn.h>
#include <vulkan/vulkan.h>

extern VkBuffer uniformBuffers[];
extern VkDeviceMemory uniformBuffersMemory[];
extern void *uniformBuffersMapped[];

// Creates uniform buffers.
void createUniformBuffers();

// Updates model, view, projection matrices in uniform buffer.
void updateUniformBuffer(uint32_t currentImage);

// Destroys uniform buffers.
void destroyUniformBuffers();
