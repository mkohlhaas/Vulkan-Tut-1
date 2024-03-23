#include "buffer.h"
#include "cmdBuffer.h"
#include "device.h"
#include "error.h"
#include "image.h"
#include "physical.h"
#include "stb_image.h"
#include <string.h>
#include <vulkan/vulkan_core.h>

static void createTextureImageView(VkImage image, VkImageView *imageView) {
  createImageView(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, imageView);
}

// file system → staging buffer (CPU/RAM) → image memory (GPU/VRAM)
void createTextureImage(const char *fileName, VkImage *image, VkImageView *imageView, VkDeviceMemory *imageMemory) {
  // load image file
  int width, height, _channels;
  stbi_uc *pixels = stbi_load(fileName, &width, &height, &_channels, STBI_rgb_alpha);

  if (!pixels) {
    logExit("Couldn't open texture file %s", fileName);
  }

  static const int imageChannels = 4;
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

  createTextureImageView(*image, imageView);

  // cleanup stb image file and staging buffer
  stbi_image_free(pixels);
  destroyBuffer(stagingBuffer, stagingBufferMemory);
}

void destroyTextureImage(VkImage image, VkImageView imageView, VkDeviceMemory imageMemory) {
  destroyImageView(imageView);
  destroyImage(image, imageMemory);
}

void createTextureSampler(VkSampler *sampler) {
  VkPhysicalDeviceProperties properties = {};
  vkGetPhysicalDeviceProperties(physicalDevice, &properties);

  VkSamplerCreateInfo samplerInfo = {
      .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
      .magFilter = VK_FILTER_LINEAR,
      .minFilter = VK_FILTER_LINEAR,
      .addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .anisotropyEnable = VK_TRUE,
      .maxAnisotropy = properties.limits.maxSamplerAnisotropy,
      .borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
      .unnormalizedCoordinates = VK_FALSE,
      .compareEnable = VK_FALSE,
      .compareOp = VK_COMPARE_OP_ALWAYS,
      .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
  };

  EH(vkCreateSampler(device, &samplerInfo, nullptr, sampler));
}

void destroyTextureSampler(VkSampler sampler) { vkDestroySampler(device, sampler, NULL); }
