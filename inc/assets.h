#pragma once

#include <vulkan/vulkan_core.h>

extern VkImageView textureImageView[];
extern VkSampler textureSampler;

// Loads all necessary textures files.
void loadAssets();

// Unloads all textures files.
void unloadAssets();
