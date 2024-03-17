#include "device.h"
#include "error.h"
#include <vulkan/vulkan.h>

VkSemaphore imageAvailableSemaphore = VK_NULL_HANDLE;
VkSemaphore renderFinishedSemaphore = VK_NULL_HANDLE;
VkFence inFlightFence = VK_NULL_HANDLE;

void createSyncObjects() {
  VkSemaphoreCreateInfo semaphoreInfo = {.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};

  VkFenceCreateInfo fenceInfo = {
      .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
      .flags = VK_FENCE_CREATE_SIGNALED_BIT,
  };

  EH(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore));
  EH(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore));
  EH(vkCreateFence(device, &fenceInfo, nullptr, &inFlightFence));
}

void cleanSyncObjects() {
  vkDestroySemaphore(device, renderFinishedSemaphore, nullptr);
  vkDestroySemaphore(device, imageAvailableSemaphore, nullptr);
  vkDestroyFence(device, inFlightFence, nullptr);
}
