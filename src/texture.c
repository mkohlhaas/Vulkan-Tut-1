#include "buffer.h"
#include "cmdBuffer.h"
#include "device.h"
#include "error.h"
#include "stb_image.h"
#include <string.h>
#include <vulkan/vulkan_core.h>

static const int imageChannels = 4;

static void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
                        VkMemoryPropertyFlags properties, VkImage *image, VkDeviceMemory *imageMemory) {

  VkImageCreateInfo imageInfo = {
      .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
      .imageType = VK_IMAGE_TYPE_2D,
      .extent = {width, height, 1},
      .format = format,
      .tiling = tiling,
      .usage = usage,
      .mipLevels = 1,
      .arrayLayers = 1,
      .samples = VK_SAMPLE_COUNT_1_BIT,
  };

  EH(vkCreateImage(device, &imageInfo, NULL, image));

  VkMemoryRequirements memRequirements;
  vkGetImageMemoryRequirements(device, *image, &memRequirements);

  uint32_t memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);
  VkMemoryAllocateInfo allocInfo = {
      .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
      .allocationSize = memRequirements.size,
      .memoryTypeIndex = memoryTypeIndex,
  };

  // allocate image memory and bind it to image
  EH(vkAllocateMemory(device, &allocInfo, NULL, imageMemory));
  EH(vkBindImageMemory(device, *image, *imageMemory, 0));
}

static void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout) {
  VkCommandBuffer commandBuffer = beginSingleTimeCommands();

  // image memory barrier (pipeline barrier)
  VkImageMemoryBarrier barrier = {
      .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
      .oldLayout = oldLayout,
      .newLayout = newLayout,
      .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      .image = image,
      .subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1},
  };

  VkPipelineStageFlags sourceStage;
  VkPipelineStageFlags destinationStage;

  if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
    barrier.srcAccessMask = 0;
    barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

    sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
  } else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL &&
             newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
  } else {
    logExit("Unsupported layout transition");
  }

  vkCmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0, NULL, 0, NULL, 1, &barrier);

  endSingleTimeCommands(commandBuffer);
}

static void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) {
  VkCommandBuffer commandBuffer = beginSingleTimeCommands();

  VkBufferImageCopy region = {
      .bufferOffset = 0,
      .bufferRowLength = 0,
      .bufferImageHeight = 0,
      .imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
      .imageSubresource.mipLevel = 0,
      .imageSubresource.baseArrayLayer = 0,
      .imageSubresource.layerCount = 1,
      .imageOffset = {0, 0, 0},
      .imageExtent = {width, height, 1},
  };

  vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

  endSingleTimeCommands(commandBuffer);
}

// file system → staging buffer (CPU/RAM) → image memory (GPU/VRAM)
void createTextureImage(const char *fileName, VkImage *image, VkDeviceMemory *imageMemory) {
  // load image file
  int width, height, _channels;
  stbi_uc *pixels = stbi_load(fileName, &width, &height, &_channels, STBI_rgb_alpha);

  if (!pixels) {
    logExit("Couldn't open texture file %s", fileName);
  }

  VkDeviceSize imageSize = width * height * imageChannels;
  dbgPrint("Image file: %s has width: %d, height: %d and size: %lu\n", fileName, width, height, imageSize);

  // create staging buffer
  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  int bufferUsageFlags = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
  int memoryProperties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
  createBuffer(imageSize, bufferUsageFlags, memoryProperties, &stagingBuffer, &stagingBufferMemory);

  // transfer image to mapped staging buffer
  void *data;
  EH(vkMapMemory(device, stagingBufferMemory, 0, imageSize, 0, &data));
  memcpy(data, pixels, imageSize);
  vkUnmapMemory(device, stagingBufferMemory);

  // create device local image (VkImage)
  VkFormat format = VK_FORMAT_R8G8B8A8_SRGB;
  VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
  VkImageUsageFlags usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  createImage(width, height, format, tiling, usage, properties, image, imageMemory);

  // transition to transfer destination optimal layout
  VkImageLayout oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  VkImageLayout newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
  transitionImageLayout(*image, VK_FORMAT_R8G8B8A8_SRGB, oldLayout, newLayout);

  // copy staging buffer to image using the new layout
  copyBufferToImage(stagingBuffer, *image, width, height);

  // transition to shader optimized layout
  oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
  newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  transitionImageLayout(*image, VK_FORMAT_R8G8B8A8_SRGB, oldLayout, newLayout);

  // cleanup stb image file and staging buffer
  stbi_image_free(pixels);
  destroyBuffer(stagingBuffer, stagingBufferMemory);
}

void destroyTextureImage(VkImage image, VkDeviceMemory imageMemory) {
  vkDestroyImage(device, image, nullptr);
  vkFreeMemory(device, imageMemory, nullptr);
}
