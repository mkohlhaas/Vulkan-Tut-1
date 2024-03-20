#pragma once

#include <vulkan/vulkan_core.h>

extern VkRenderPass renderPass;

// Creates a simple render pass.
void createRenderPass();

// Destroys render pass.
void closeRenderPass();
