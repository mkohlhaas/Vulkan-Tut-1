#include "assets.h"
#include "device.h"
#include "error.h"
#include "globals.h"
#include "uniformBuffers.h"
#include <vulkan/vulkan.h>

VkDescriptorSetLayout descriptorSetLayout;
VkDescriptorSet descriptorSets[MAX_FRAMES_IN_FLIGHT];

static VkDescriptorPool descriptorPool;

void destroyDescriptorSet() {
  vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
  vkDestroyDescriptorPool(device, descriptorPool, nullptr);
}

static void createDescriptorPool() {
  VkDescriptorPoolSize poolSize[] = {{
                                         .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                                         .descriptorCount = MAX_FRAMES_IN_FLIGHT,
                                     },
                                     {
                                         .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                                         .descriptorCount = MAX_FRAMES_IN_FLIGHT,
                                     }};

  VkDescriptorPoolCreateInfo poolInfo = {
      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
      .poolSizeCount = sizeof(poolSize) / sizeof(VkDescriptorPoolSize),
      .pPoolSizes = poolSize,
      .maxSets = MAX_FRAMES_IN_FLIGHT,
  };

  EH(vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool))
}

static void createDescriptorSetLayout() {
  VkDescriptorSetLayoutBinding uboLayoutBinding = {
      .binding = 0,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
      .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
  };

  VkDescriptorSetLayoutBinding samplerLayoutBinding = {
      .binding = 1,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
      .pImmutableSamplers = NULL,
      .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
  };

  VkDescriptorSetLayoutBinding bindings[] = {uboLayoutBinding, samplerLayoutBinding};

  VkDescriptorSetLayoutCreateInfo layoutInfo = {
      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
      .bindingCount = sizeof(bindings) / sizeof(VkDescriptorSetLayoutBinding),
      .pBindings = bindings,
  };

  EH(vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout));
}

void createDescriptorSets() {
  // create descriptor set layout
  createDescriptorSetLayout();

  // create descriptor pool
  createDescriptorPool();

  // allocate descriptor sets
  VkDescriptorSetLayout layouts[MAX_FRAMES_IN_FLIGHT] = {descriptorSetLayout, descriptorSetLayout};
  VkDescriptorSetAllocateInfo allocInfo = {
      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
      .descriptorPool = descriptorPool,
      .descriptorSetCount = MAX_FRAMES_IN_FLIGHT,
      .pSetLayouts = layouts,
  };

  EH(vkAllocateDescriptorSets(device, &allocInfo, descriptorSets));

  // connect/docking uniform buffer to descriptor sets
  for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    // make the connection
    VkDescriptorBufferInfo bufferInfo = {
        .buffer = uniformBuffers[i],
        .offset = 0,
        .range = sizeof(UniformBufferObject),
    };

    // TODO: uses only first texture image view
    // descriptorSets should be a 2-dimensional array → use GLIB2 library (e.g. array of arrays)
    VkDescriptorImageInfo imageInfo = {
        .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        .imageView = textureImageView[0],
        .sampler = textureSampler,
    };

    // update descriptor sets
    VkWriteDescriptorSet descriptorWrites[] = {{
                                                   .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                                                   .dstSet = descriptorSets[i],
                                                   .dstBinding = 0,
                                                   .dstArrayElement = 0,
                                                   .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                                                   .descriptorCount = 1,
                                                   .pBufferInfo = &bufferInfo,
                                               },
                                               {
                                                   .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                                                   .dstSet = descriptorSets[i],
                                                   .dstBinding = 1,
                                                   .dstArrayElement = 0,
                                                   .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                                                   .descriptorCount = 1,
                                                   .pImageInfo = &imageInfo,
                                               }};

    uint32_t numDescriptorWrites = sizeof(descriptorWrites) / sizeof(VkWriteDescriptorSet);
    vkUpdateDescriptorSets(device, numDescriptorWrites, descriptorWrites, 0, nullptr);
  }
}
