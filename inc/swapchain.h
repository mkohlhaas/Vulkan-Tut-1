#pragma once

#include <vulkan/vulkan.h>

extern VkSwapchainKHR swapchain;
extern VkFormat swapchainImageFormat;
extern VkExtent2D swapchainExtent;
extern uint32_t swapchainImagesCount;
extern VkImage *swapchainImages;
extern VkImageView *swapchainImageViews;
extern VkFramebuffer *framebuffers;

// Sets `swapchain`, `swapchainImageFormat`, `swapchainExtent`, `swapchainImageCount`, `swapchainImageViews` variables.
void createSwapchain();

// Destroys swapchain and its image views.
void cleanSwapchain();

// Recreates swapchain (in case of window resize/minimization).
void recreateSwapchain();
