#pragma once

#include <vulkan/vulkan_core.h>

extern VkImageView depthImageView;

// Creates depth image and associated memory and image view.
void createDepthImage();

// Destroys depth image and associated memory and image view.
void destroyDepthImage();

// Destroys depth image and creates it anew including associated memory and image view.
void recreateDepthImage();
