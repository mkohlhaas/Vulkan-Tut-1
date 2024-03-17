#pragma once

#include <vulkan/vulkan.h>

extern VkFramebuffer *framebuffers;

// Creates swapchain's frame buffers.
void createFramebuffers();

// Destroys swapchain's frame buffers.
void cleanFramebuffers();
