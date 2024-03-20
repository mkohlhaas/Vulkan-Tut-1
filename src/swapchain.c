#include "device.h"
#include "error.h"
#include "physical.h"
#include "renderpass.h"
#include "surface.h"
#include "window.h"
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

VkSwapchainKHR swapchain = VK_NULL_HANDLE;
VkFormat swapchainImageFormat = VK_FORMAT_B8G8R8A8_SRGB;
VkExtent2D swapchainExtent;
uint32_t swapchainImagesCount;
VkImage *swapchainImages = nullptr;
VkImageView *swapchainImageViews = nullptr;
VkFramebuffer *framebuffers = nullptr;

static void createFramebuffers() {
  free(framebuffers);
  framebuffers = malloc(sizeof(VkFramebuffer) * swapchainImagesCount);
  if (!framebuffers) {
    logExit("Not enough memory");
  }

  // TODO: is loop really necessary or can we just set `attachmentCount` ?
  for (int i = 0; i < swapchainImagesCount; i++) {
    VkFramebufferCreateInfo framebufferCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        .renderPass = renderPass,
        .attachmentCount = 1,
        .pAttachments = &swapchainImageViews[i],
        .width = swapchainExtent.width,
        .height = swapchainExtent.height,
        .layers = 1,
    };

    EH(vkCreateFramebuffer(device, &framebufferCreateInfo, nullptr, &framebuffers[i]));
  }
}

static void destroyFramebuffers() {
  for (int i = 0; i < swapchainImagesCount; i++) {
    vkDestroyFramebuffer(device, framebuffers[i], nullptr);
  }
}

static void createSwapchainImageViews() {
  VkImageView view;

  free(swapchainImageViews);
  swapchainImageViews = malloc(sizeof(VkImageView) * swapchainImagesCount);
  if (!swapchainImageViews) {
    logExit("Not enough memory");
  }

  for (int i = 0; i < swapchainImagesCount; i++) {
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

void createSwapchain() {
  VkSurfaceCapabilitiesKHR surfaceCapabilities;
  EH(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &surfaceCapabilities));

  swapchainExtent = surfaceCapabilities.currentExtent;
  uint32_t queueFamilyIndex = getQueueFamilyIndex();

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
      .presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR,
      .clipped = VK_TRUE,
  };

  // create swapchain
  EH(vkCreateSwapchainKHR(device, &swapchainCreateInfoKHR, nullptr, &swapchain));

  // get swapchain images
  vkGetSwapchainImagesKHR(device, swapchain, &swapchainImagesCount, nullptr);
  free(swapchainImages);
  swapchainImages = malloc(sizeof(VkImage) * swapchainImagesCount);
  if (!swapchainImages) {
    logExit("Not enough memory");
  }
  EH(vkGetSwapchainImagesKHR(device, swapchain, &swapchainImagesCount, swapchainImages));

  createSwapchainImageViews();

  createFramebuffers();
}

void destroySwapchain() {
  destroyFramebuffers();

  for (int i = 0; i < swapchainImagesCount; i++) {
    vkDestroyImageView(device, swapchainImageViews[i], nullptr);
  }

  vkDestroySwapchainKHR(device, swapchain, nullptr);
}

void recreateSwapchain() {
  int width, height;
  glfwGetWindowSize(window, &width, &height);

  // minimized window
  while (width == 0 || height == 0) {
    glfwGetWindowSize(window, &width, &height);
    glfwWaitEvents();
  }

  deviceWaitIdle();

  destroySwapchain();
  createSwapchain();
}
