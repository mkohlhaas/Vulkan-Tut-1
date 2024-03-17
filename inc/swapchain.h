#pragma once

#include <vulkan/vulkan.h>

extern VkFormat swapchainImageFormat;
extern VkExtent2D swapchainExtent;
extern uint32_t swapchainImageCount;
extern VkImageView *swapchainImageViews;

void createSwapchain();
void createSwapchainImageViews();
void cleanSwapchain();
