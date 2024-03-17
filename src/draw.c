#include "cmdBuffer.h"
#include "device.h"
#include "error.h"
#include "record.h"
#include "swapchain.h"
#include "sync.h"
#include <vulkan/vulkan.h>

static image_index_t imageIndex = UINT32_MAX;

// Waits for `inFlightFence`.
static void waitForInFlightFence() {
  EH(vkWaitForFences(device, 1, &inFlightFence, VK_TRUE, UINT64_MAX));
  EH(vkResetFences(device, 1, &inFlightFence));
}

// Signals `imageAvailableSemaphore`.
static image_index_t acquireNextImage() {
  vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
  return imageIndex;
}

static void resetCmdBuffer() { EH(vkResetCommandBuffer(cmdBuffer, 0)); }

// Reset comamand buffer and re-record it.
static void recCmdBuffer() {
  resetCmdBuffer();
  recordCmdBuffer(imageIndex);
};

// Waits for `imageAvailableSemaphore`.
// Signals `inFlightFence` and `renderFinishedSemaphore` when queue is finished.
static void submitQueue() {
  VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

  VkSubmitInfo submitInfo = {
      .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
      .waitSemaphoreCount = 1,
      .pWaitSemaphores = &imageAvailableSemaphore,
      .pWaitDstStageMask = waitStages,
      .commandBufferCount = 1,
      .pCommandBuffers = &cmdBuffer,
      .signalSemaphoreCount = 1,
      .pSignalSemaphores = &renderFinishedSemaphore,
  };

  EH(vkQueueSubmit(getDeviceQueue(), 1, &submitInfo, inFlightFence));
}

// Waits for `renderFinishedSemaphore`.
static void presentQueue() {
  VkPresentInfoKHR presentInfo = {
      .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
      .waitSemaphoreCount = 1,
      .pWaitSemaphores = &renderFinishedSemaphore,
      .swapchainCount = 1,
      .pSwapchains = &swapchain,
      .pImageIndices = &imageIndex,
  };
  EH(vkQueuePresentKHR(getDeviceQueue(), &presentInfo));
}

void drawFrame() {
  waitForInFlightFence();
  imageIndex = acquireNextImage();
  recCmdBuffer();
  submitQueue();
  presentQueue();
}
