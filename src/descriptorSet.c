#include "device.h"
#include "error.h"
#include "globals.h"
#include "uniformBuffers.h"
#include <vulkan/vulkan.h>

#define DST_BINDING 0

VkDescriptorSetLayout descriptorSetLayout;
VkDescriptorSet descriptorSets[MAX_FRAMES_IN_FLIGHT];

static VkDescriptorPool descriptorPool;

void destroyDescriptorSet() {
  vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
  vkDestroyDescriptorPool(device, descriptorPool, nullptr);
}

static void createDescriptorPool() {
  VkDescriptorPoolSize poolSize = {
      .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
      .descriptorCount = MAX_FRAMES_IN_FLIGHT,
  };

  VkDescriptorPoolCreateInfo poolInfo = {
      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
      .poolSizeCount = 1,
      .pPoolSizes = &poolSize,
      .maxSets = MAX_FRAMES_IN_FLIGHT,
  };

  EH(vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool))
}

static void createDescriptorSetLayout() {
  VkDescriptorSetLayoutBinding uboLayoutBindings[] = {
      {
          .binding = DST_BINDING,
          .descriptorCount = 1,
          .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
          .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
      },
  };

  VkDescriptorSetLayoutCreateInfo layoutInfo = {
      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
      .bindingCount = sizeof(uboLayoutBindings) / sizeof(VkDescriptorSetLayoutBinding),
      .pBindings = uboLayoutBindings,
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
    VkDescriptorBufferInfo bufferInfo[] = {
        {
            .buffer = uniformBuffers[i],
            .offset = 0,
            .range = sizeof(UniformBufferObject),
        },
    };

    // update descriptor set
    VkWriteDescriptorSet descriptorWrite = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = descriptorSets[i],
        .dstBinding = DST_BINDING,
        .dstArrayElement = 0,
        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = sizeof(bufferInfo) / sizeof(VkDescriptorBufferInfo),
        .pBufferInfo = bufferInfo,
    };

    vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);
  }
}
