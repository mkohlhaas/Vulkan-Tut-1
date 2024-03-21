#pragma once

#include <vulkan/vulkan_core.h>

extern VkPipeline pipeline;
extern VkPipelineLayout pipelineLayout;

// Creates graphics pipeline.
void createPipeline();

// Destroys graphics pipeline.
void destroyPipeline();
