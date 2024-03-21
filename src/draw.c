#include "cmdBuffer.h"
#include "device.h"
#include "error.h"
#include "globals.h"
#include "record.h"
#include "swapchain.h"
#include "sync.h"
#include "uniformBuffers.h"
#include "window.h"
#include <stdbool.h>
#include <vulkan/vulkan.h>

static image_index_t imageIndex = UINT32_MAX;

// Waits for `inFlightFence`.
static void waitForInFlightFence() {
  EH(vkWaitForFences(device, 1, &inFlightFence[currentFrame], VK_TRUE, UINT64_MAX));
}

static void resetFence() { EH(vkResetFences(device, 1, &inFlightFence[currentFrame])); }

// Signals `imageAvailableSemaphore`.
static bool acquireNextImage() {
  err = vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, imageAvailableSemaphore[currentFrame], VK_NULL_HANDLE,
                              &imageIndex);

  if (err == VK_ERROR_OUT_OF_DATE_KHR) {
    recreateSwapchain();
    imageIndex = UINT32_MAX;
    return false;
  } else if (err != VK_SUCCESS && err != VK_SUBOPTIMAL_KHR) {
    handleError(__FILE_NAME__, __LINE__);
  }

  return true;
}

static void resetCmdBuffer() { EH(vkResetCommandBuffer(cmdBuffers[currentFrame], 0)); }

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
      .pWaitSemaphores = &imageAvailableSemaphore[currentFrame],
      .pWaitDstStageMask = waitStages,
      .commandBufferCount = 1,
      .pCommandBuffers = &cmdBuffers[currentFrame],
      .signalSemaphoreCount = 1,
      .pSignalSemaphores = &renderFinishedSemaphore[currentFrame],
  };

  EH(vkQueueSubmit(deviceQueue, 1, &submitInfo, inFlightFence[currentFrame]));
}

// Waits for `renderFinishedSemaphore`.
static void presentQueue() {
  VkPresentInfoKHR presentInfo = {
      .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
      .waitSemaphoreCount = 1,
      .pWaitSemaphores = &renderFinishedSemaphore[currentFrame],
      .swapchainCount = 1,
      .pSwapchains = &swapchain,
      .pImageIndices = &imageIndex,
  };
  err = vkQueuePresentKHR(deviceQueue, &presentInfo);

  if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR || framebufferResized) {
    framebufferResized = false;
    recreateSwapchain();
  } else if (err != VK_SUCCESS) {
    handleError(__FILE_NAME__, __LINE__);
  }
}

void updateFrameCounter() { currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT; }

void drawFrame() {
  waitForInFlightFence();
  updateFrameCounter();
  if (!acquireNextImage()) {
    return;
  }
  updateUniformBuffer(currentFrame);
  resetFence();
  recCmdBuffer();
  submitQueue();
  presentQueue();
}
