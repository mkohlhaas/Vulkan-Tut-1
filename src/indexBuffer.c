#include "buffer.h"
#include "device.h"
#include "error.h"
#include "globals.h"
#include "types.h"
#include <string.h>
#include <vulkan/vulkan_core.h>

VkBuffer indexBuffer;
VkDeviceMemory indexBufferMemory;

void createIndexBuffer() {
  VkDeviceSize bufferSize = numIndices * sizeof(vertex_index_t);

  // create staging buffer
  VkBufferUsageFlags usages = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
  VkMemoryPropertyFlags props = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  createBuffer(bufferSize, usages, props, &stagingBuffer, &stagingBufferMemory);

  // create index buffer
  usages = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
  props = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  createBuffer(bufferSize, usages, props, &indexBuffer, &indexBufferMemory);

  // copy indices to staging buffer
  void *data;
  EH(vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data));
  memcpy(data, indices, bufferSize);
  vkUnmapMemory(device, stagingBufferMemory);

  // copy staging to index buffer
  copyBuffer(stagingBuffer, indexBuffer, bufferSize);

  // destroy staging buffer and free its bound memory
  destroyBuffer(stagingBuffer, stagingBufferMemory);
}

void destroyIndexBuffer() { destroyBuffer(indexBuffer, indexBufferMemory); }
