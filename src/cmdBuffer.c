#include "device.h"
#include "error.h"
#include "physical.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

VkCommandPool cmdPool;
VkCommandBuffer cmdBuffer;

void allocateCommandBuffer() {
  VkCommandBufferAllocateInfo allocateInfo = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .commandPool = cmdPool,
      .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
      .commandBufferCount = 1,
  };
  EH(vkAllocateCommandBuffers(device, &allocateInfo, &cmdBuffer));
}

void createCmdBuffer() {
  VkCommandPoolCreateInfo createInfo = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
      .queueFamilyIndex = getQueueFamilyIndex(),
  };
  EH(vkCreateCommandPool(device, &createInfo, nullptr, &cmdPool));
  allocateCommandBuffer();
}

void cleanCmdBuffer() { vkDestroyCommandPool(device, cmdPool, nullptr); }
