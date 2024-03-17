#pragma once

#include <vulkan/vulkan.h>

extern VkSwapchainKHR swapchain;
extern VkFormat swapchainImageFormat;
extern VkExtent2D swapchainExtent;
extern uint32_t swapchainImagesCount;
extern VkImage *swapchainImages;
extern VkImageView *swapchainImageViews;

// Sets `swapchain`, `swapchainImageFormat`, `swapchainExtent`, `swapchainImageCount`, `swapchainImageViews` variables.
void createSwapchain();

// Destroys swapchain andits image views.
void cleanSwapchain();
