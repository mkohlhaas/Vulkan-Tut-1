#include "device.h"
#include "error.h"
#include "globals.h"
#include "physical.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

VkCommandPool cmdPool;
VkCommandBuffer cmdBuffers[FRAMES_IN_FLIGHT];

static void allocateCommandBuffers() {
  VkCommandBufferAllocateInfo allocateInfo = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .commandPool = cmdPool,
      .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
      .commandBufferCount = FRAMES_IN_FLIGHT,
  };
  EH(vkAllocateCommandBuffers(device, &allocateInfo, cmdBuffers));
}

void createCmdBuffers() {
  VkCommandPoolCreateInfo createInfo = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
      .queueFamilyIndex = getQueueFamilyIndex(),
  };
  EH(vkCreateCommandPool(device, &createInfo, nullptr, &cmdPool));
  allocateCommandBuffers();
}

void destroyCmdBuffers() { vkDestroyCommandPool(device, cmdPool, nullptr); }

VkCommandBuffer beginSingleTimeCommands() {
  VkCommandBufferAllocateInfo allocInfo = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
      .commandPool = cmdPool,
      .commandBufferCount = 1,
  };

  VkCommandBuffer commandBuffer;
  EH(vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer));

  VkCommandBufferBeginInfo beginInfo = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
      .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
  };

  EH(vkBeginCommandBuffer(commandBuffer, &beginInfo));

  return commandBuffer;
}

void endSingleTimeCommands(VkCommandBuffer commandBuffer) {
  EH(vkEndCommandBuffer(commandBuffer));

  VkSubmitInfo submitInfo = {
      .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
      .commandBufferCount = 1,
      .pCommandBuffers = &commandBuffer,
  };

  EH(vkQueueSubmit(deviceQueue, 1, &submitInfo, VK_NULL_HANDLE));
  EH(vkQueueWaitIdle(deviceQueue));

  vkFreeCommandBuffers(device, cmdPool, 1, &commandBuffer);
}
