#pragma once

#include <vulkan/vulkan_core.h>

extern VkInstance instance;

// Opens Vulkan™ library.
void createInstance();

// Closes Vulkan™ library.
void closeInstance();
