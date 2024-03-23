#pragma once

#include <vulkan/vulkan_core.h>

// Creates image.
void createImage(uint32_t, uint32_t, VkFormat, VkImageTiling, VkImageUsageFlags, VkMemoryPropertyFlags, VkImage *,
                 VkDeviceMemory *);

// Creates image view based on existing image.
void createImageView(VkImage, VkFormat, VkImageAspectFlags, VkImageView *);

// Destroys image.
void destroyImage(VkImage, VkDeviceMemory);

// Destroys image view.
void destroyImageView(VkImageView);

// Copies buffer to image.
void copyBufferToImage(VkBuffer, VkImage, uint32_t, uint32_t);

// Transitions image layout.
void transitionImageLayout(VkImage, VkFormat, VkImageLayout, VkImageLayout);
