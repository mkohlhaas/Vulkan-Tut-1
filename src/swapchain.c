#include "device.h"
#include "error.h"
#include "physical.h"
#include "surface.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

VkSwapchainKHR swapchain;
VkFormat swapchainImageFormat = VK_FORMAT_B8G8R8A8_SRGB;
VkExtent2D swapchainExtent;
uint32_t swapchainImageCount;
VkImage *swapchainImages;
VkImageView *swapchainImageViews;

// Sets `swapchain` variable and some more. (See header file.)
void createSwapchain() {

  VkSurfaceCapabilitiesKHR surfaceCapabilities;
  EH(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &surfaceCapabilities));

  swapchainExtent = surfaceCapabilities.currentExtent;

  VkSwapchainCreateInfoKHR swapchainCreateInfoKHR = {
      .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
      .surface = surface,
      .minImageCount = surfaceCapabilities.minImageCount,
      .imageFormat = swapchainImageFormat,
      .imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
      .imageExtent = swapchainExtent,
      .imageArrayLayers = 1,
      .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
      .queueFamilyIndexCount = 1,
      .pQueueFamilyIndices = &queueFamilyIndex,
      .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
      .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
      .presentMode = VK_PRESENT_MODE_FIFO_KHR,
      .clipped = VK_TRUE,
  };

  // create swapchain
  EH(vkCreateSwapchainKHR(device, &swapchainCreateInfoKHR, nullptr, &swapchain));

  // get swapchain images
  vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, nullptr);
  swapchainImages = malloc(sizeof(VkImage) * swapchainImageCount);
  if (!swapchainImages) {
    log("Not enough memory");
    exit(EXIT_FAILURE);
  }
  EH(vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, swapchainImages));
}

void createSwapchainImageViews() {
  VkImageView view;

  swapchainImageViews = malloc(sizeof(VkImageView) * swapchainImageCount);
  if (!swapchainImageViews) {
    log("Not enough memory");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < swapchainImageCount; i++) {
    const VkImageViewCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .image = swapchainImages[i],
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = swapchainImageFormat,
        .subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1},
    };
    EH(vkCreateImageView(device, &createInfo, nullptr, &view));
    swapchainImageViews[i] = view;
  }
}