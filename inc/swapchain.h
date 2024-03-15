#pragma once

#include <vulkan/vulkan.h>

extern VkSwapchainKHR swapchain;
extern VkFormat swapchainImageFormat;
extern VkExtent2D swapchainExtent;
extern uint32_t swapchainImageCount;
extern VkImage *swapchainImages;
extern VkImageView *swapchainImageViews;

void createSwapchain();
void createSwapchainImageViews();
