#pragma once

#include <vulkan/vulkan_core.h>

// Creates a texture image with associated memory from file `fileName`.
void createTextureImage(const char *fileName, VkImage *image, VkImageView *imageView, VkDeviceMemory *imageMemory);

// Destroys texture image and its associated memory.
void destroyTextureImage(VkImage image, VkImageView imageView, VkDeviceMemory imageMemory);

// Creates a texture sampler.
void createTextureSampler(VkSampler *sampler);

// Destroys sampler.
void destroyTextureSampler(VkSampler sampler);
