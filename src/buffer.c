#include "cmdBuffer.h"
#include "device.h"
#include "error.h"
#include "physical.h"
#include <stdint.h>
#include <vulkan/vulkan_core.h>

uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
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
  VkCommandBuffer tmpCmdBuffer = beginSingleTimeCommands();

  // copy srcBuffer to dstBuffer
  VkBufferCopy copyRegion = {
      .size = size,
  };
  vkCmdCopyBuffer(tmpCmdBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

  endSingleTimeCommands(tmpCmdBuffer);
}

void destroyBuffer(VkBuffer buffer, VkDeviceMemory memory) {
  vkDestroyBuffer(device, buffer, nullptr);
  vkFreeMemory(device, memory, nullptr);
}
