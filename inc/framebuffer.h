#pragma once

#include <vulkan/vulkan.h>

extern VkFramebuffer *swapchainFramebuffers;

void createFramebuffers();
void cleanFramebuffers();
