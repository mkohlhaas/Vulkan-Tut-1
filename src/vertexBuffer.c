#include "buffer.h"
#include "device.h"
#include "error.h"
#include "globals.h"
#include "mesh.h"
#include "types.h"
#include <string.h>
#include <vulkan/vulkan_core.h>

VkBuffer vertexBuffer = VK_NULL_HANDLE;
VkDeviceMemory vertexBufferMemory = VK_NULL_HANDLE;

void createVertexBuffer() {
  // create staging buffer
  VkDeviceSize bufferSize = numVertices * sizeof(Vertex);
  VkBufferUsageFlags usages = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
  VkMemoryPropertyFlags props = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  createBuffer(bufferSize, usages, props, &stagingBuffer, &stagingBufferMemory);

  // creates vertex buffer using local GPU memory
  usages = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  props = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  createBuffer(bufferSize, usages, props, &vertexBuffer, &vertexBufferMemory);

  // copy vertices to staging buffer
  void *data;
  EH(vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data));
  memcpy(data, vertices, bufferSize);
  vkUnmapMemory(device, stagingBufferMemory);

  // copy staging to vertex buffer
  copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

  // destroy staging buffer and free its bound memory
  destroyBuffer(stagingBuffer, stagingBufferMemory);
}

void destroyVertexBuffer() { destroyBuffer(vertexBuffer, vertexBufferMemory); }
