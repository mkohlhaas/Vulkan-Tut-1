#pragma once

#include <vulkan/vulkan.h>

extern VkPhysicalDevice physicalDevice;

// Selects an appropriate physical device.
void pickPhysicalDevice();

// Print some physical device information.
void printPhysicalDevices();

// Returns queue family index.
uint32_t getQueueFamilyIndex();
