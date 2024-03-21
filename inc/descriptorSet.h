#pragma once

#include <vulkan/vulkan.h>

// Model, view, projection matrices descriptor set layout
extern VkDescriptorSetLayout descriptorSetLayout;
extern VkDescriptorSet descriptorSets[];

// Creates ubo (Uniform Buffer Object) descriptor sets
void createDescriptorSets();

// Destroys ubo (Uniform Buffer Object) descriptor set layout
void destroyDescriptorSet();
