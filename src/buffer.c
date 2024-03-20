#include "cmdBuffer.h"
#include "device.h"
#include "error.h"
#include "physical.h"
#include <stdint.h>
#include <vulkan/vulkan_core.h>

static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

  for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
    if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
      return i;
    }
  }
  logExit("Failed to find suitable memory type");
}

void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer *buffer,
                  VkDeviceMemory *bufferMemory) {
  // create buffer
  VkBufferCreateInfo bufferInfo = {
      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      .size = size,
      .usage = usage,
  };
  EH(vkCreateBuffer(device, &bufferInfo, nullptr, buffer));

  // memory requirements
  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements(device, *buffer, &memRequirements);

  // find suitable memory
  uint32_t memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

  // allocate memory
  VkMemoryAllocateInfo allocInfo = {
      .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
      .allocationSize = memRequirements.size,
      .memoryTypeIndex = memoryTypeIndex,
  };
  EH(vkAllocateMemory(device, &allocInfo, nullptr, bufferMemory));

  // bind memory to buffer
  EH(vkBindBufferMemory(device, *buffer, *bufferMemory, 0));
}

void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
  // allocate temp commmand buffer
  VkCommandBufferAllocateInfo allocInfo = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
      .commandPool = cmdPool,
      .commandBufferCount = 1,
  };

  VkCommandBuffer tmpCmdBuffer;
  EH(vkAllocateCommandBuffers(device, &allocInfo, &tmpCmdBuffer));

  // record copy command into temp command buffer
  {
    // begin command buffer
    VkCommandBufferBeginInfo beginInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    };

    EH(vkBeginCommandBuffer(tmpCmdBuffer, &beginInfo));

    // copy src to dst
    VkBufferCopy copyRegion = {
        .size = size,
    };
    vkCmdCopyBuffer(tmpCmdBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    // end command buffer
    EH(vkEndCommandBuffer(tmpCmdBuffer));
  }

  // submit temp command buffer
  VkSubmitInfo submitInfo = {
      .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
      .commandBufferCount = 1,
      .pCommandBuffers = &tmpCmdBuffer,
  };

  EH(vkQueueSubmit(deviceQueue, 1, &submitInfo, VK_NULL_HANDLE));

  // wait for copy operation to be finished
  EH(vkQueueWaitIdle(deviceQueue));

  // free temp command buffer
  vkFreeCommandBuffers(device, cmdPool, 1, &tmpCmdBuffer);
}

void destroyBuffer(VkBuffer buffer, VkDeviceMemory memory) {
  vkDestroyBuffer(device, buffer, nullptr);
  vkFreeMemory(device, memory, nullptr);
}
