#include "device.h"
#include "error.h"
#include "globals.h"
#include "physical.h"
#include "types.h"
#include <stdint.h>
#include <string.h>
#include <vulkan/vulkan_core.h>

VkBuffer vertexBuffer = VK_NULL_HANDLE;
VkDeviceMemory vertexBufferMemory = VK_NULL_HANDLE;

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

void createVertexBuffer() {
  // create buffer
  VkDeviceSize bufferSize = numVertices * sizeof(Vertex);
  VkBufferCreateInfo bufferInfo = {
      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      .size = bufferSize,
      .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
  };
  EH(vkCreateBuffer(device, &bufferInfo, nullptr, &vertexBuffer))

  // query memory requirements
  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements(device, vertexBuffer, &memRequirements);

  // find suitable memory
  uint32_t memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits,
                                            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

  // allocate memory
  VkMemoryAllocateInfo allocInfo = {
      .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
      .allocationSize = memRequirements.size,
      .memoryTypeIndex = memoryTypeIndex,
  };

  EH(vkAllocateMemory(device, &allocInfo, nullptr, &vertexBufferMemory));

  // bind memory to buffer
  EH(vkBindBufferMemory(device, vertexBuffer, vertexBufferMemory, 0));

  // fill memory
  void *data;
  EH(vkMapMemory(device, vertexBufferMemory, 0, bufferSize, 0, &data));
  memcpy(data, vertices, bufferSize);
  vkUnmapMemory(device, vertexBufferMemory);
}

void closeVertexBuffer() {
  vkDestroyBuffer(device, vertexBuffer, nullptr);
  vkFreeMemory(device, vertexBufferMemory, nullptr);
}
