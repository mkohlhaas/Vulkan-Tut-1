#pragma once

#include <vulkan/vulkan.h>

extern VkPhysicalDevice physicalDevice;
extern uint32_t queueFamilyIndex;

void pickPhysicalDevice();
void printPhysicalDevices();
