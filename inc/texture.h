#pragma once

#include <vulkan/vulkan_core.h>

// Creates a texture image with associated memory from file `fileName`.
void createTextureImage(const char *fileName, VkImage *image, VkDeviceMemory *imageMemory);

// Destroys texture image and its associated memory.
void destroyTextureImage(VkImage image, VkDeviceMemory imageMemory);
