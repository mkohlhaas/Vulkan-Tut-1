#pragma once

#include <vulkan/vulkan.h>

extern VkDevice device;
extern VkQueue deviceQueue;

// Creates a logical device.
void createDevice();

// Waits for device to have finished its current work.
void deviceWaitIdle();

// Destroys logical device.
void destroyDevice();
