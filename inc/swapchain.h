#pragma once

#include <vulkan/vulkan.h>

extern VkSwapchainKHR swapchain;

// Sets `swapchain`, `swapchainImageFormat`, `swapchainExtent`, `swapchainImageCount`, `swapchainImageViews` variables.
void createSwapchain();

// Gets swapchain image format.
VkFormat getSwapchainImageFormat();

// Gets swapchain extent.
VkExtent2D getSwapchainExtent();

// Gets swapchain image count.
uint32_t getSwapchainImageCount();

// Gets swapchain image views.
VkImageView *getSwapchainImageViews();

// Destroys swapchain and its image views.
void cleanSwapchain();
