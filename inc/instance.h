#pragma once

#include <vulkan/vulkan_core.h>

extern VkInstance instance;

#ifndef Ndebug
extern VkDebugUtilsMessengerEXT debugMessenger;
#endif

void initVulkan();
