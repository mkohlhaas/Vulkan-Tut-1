#pragma once

#include <vulkan/vulkan.h>

extern VkSwapchainKHR swapchain;
extern VkFormat swapchainImageFormat;
extern VkExtent2D swapchainExtent;
extern uint32_t swapchainImagesCount;
extern VkImage *swapchainImages;
extern VkImageView *swapchainImageViews;
extern VkFramebuffer *framebuffers;

// Sets `swapchain`, `swapchainImageFormat`, `swapchainExtent`, `swapchainImageCount`, `swapchainImageViews`, `framebuffers` variables.
void createSwapchain();

// Destroys swapchain, its image views and framebuffers.
void destroySwapchain();

// Recreates swapchain (in case of window resize/minimization).
void recreateSwapchain();
