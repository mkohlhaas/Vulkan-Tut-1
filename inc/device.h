#pragma once

#include <vulkan/vulkan.h>

extern VkDevice device;

// Creates a logical device.
void createDevice();

// Gets device queue.
VkQueue getDeviceQueue();

// Waits for device to have finished its current work.
void deviceWaitIdle();

// Destroys logical device.
void cleanDevice();
