#include "device.h"
#include "error.h"
#include "globals.h"
#include <stdio.h>
#include <vulkan/vulkan.h>

VkSemaphore imageAvailableSemaphore[FRAMES_IN_FLIGHT] = {};
VkSemaphore renderFinishedSemaphore[FRAMES_IN_FLIGHT] = {};
VkFence inFlightFence[FRAMES_IN_FLIGHT] = {};

void createSyncObjects() {
  VkSemaphoreCreateInfo semaphoreInfo = {.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};

  VkFenceCreateInfo fenceInfo = {
      .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
      .flags = VK_FENCE_CREATE_SIGNALED_BIT,
  };

  for (int i = 0; i < FRAMES_IN_FLIGHT; i++) {
    EH(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore[i]));
    EH(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore[i]));
    EH(vkCreateFence(device, &fenceInfo, nullptr, &inFlightFence[i]));
  }
}

void destroySyncObjects() {
  for (int i = 0; i < FRAMES_IN_FLIGHT; i++) {
    vkDestroySemaphore(device, renderFinishedSemaphore[i], nullptr);
    vkDestroySemaphore(device, imageAvailableSemaphore[i], nullptr);
    vkDestroyFence(device, inFlightFence[i], nullptr);
  }
}
