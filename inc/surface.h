#pragma once

#include <vulkan/vulkan.h>

extern VkSurfaceKHR surface;

// Creates a window  surface.
void createSurface();

// Destroys surface.
void cleanSurface();
