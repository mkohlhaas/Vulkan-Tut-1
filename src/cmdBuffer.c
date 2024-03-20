#include "device.h"
#include "error.h"
#include "globals.h"
#include "physical.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

VkCommandPool cmdPool;
VkCommandBuffer cmdBuffers[MAX_FRAMES_IN_FLIGHT];

static void allocateCommandBuffers() {
  VkCommandBufferAllocateInfo allocateInfo = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .commandPool = cmdPool,
      .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
      .commandBufferCount = MAX_FRAMES_IN_FLIGHT,
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
