#include "device.h"
#include "image.h"
#include "swapchain.h"
#include <vulkan/vulkan_core.h>

VkImage depthImage;
VkDeviceMemory depthImageMemory;
VkImageView depthImageView;

void createDepthImage() {
  VkFormat depthFormat = VK_FORMAT_D32_SFLOAT;
  uint32_t width = swapchainExtent.width;
  uint32_t height = swapchainExtent.height;
  VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
  VkImageUsageFlags imageUsage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
  VkMemoryPropertyFlags memProperties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

  createImage(width, height, depthFormat, tiling, imageUsage, memProperties, &depthImage, &depthImageMemory);
  createImageView(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, &depthImageView);
}

void destroyDepthImage() {
  vkDestroyImageView(device, depthImageView, NULL);
  vkDestroyImage(device, depthImage, NULL);
  vkFreeMemory(device, depthImageMemory, NULL);
}

void recreateDepthImage() {
  destroyDepthImage();
  createDepthImage();
}
