#pragma once

#include <vulkan/vulkan.h>

extern VkDevice device;

// Creates a logical device.
void createDevice();

// Gets device queue.
VkQueue getDeviceQueue();

// Destroys logical device.
void cleanDevice();
