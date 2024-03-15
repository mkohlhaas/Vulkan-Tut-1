#include "clean.h"
#include "device.h"
#include "instance.h"
#include "physical.h"
#include "pipeline.h"
#include "renderpass.h"
#include "surface.h"
#include "swapchain.h"
#include "window.h"

int main(void) {
  initGlfw();
  initVulkan();
  createSurface();
#ifndef NDEBUG
  printPhysicalDevices();
#endif
  pickPhysicalDevice();
  createDevice();
  createRenderPass();
  createPipeline();
  createSwapchain();
  createSwapchainImageViews();
  mainLoop();
  cleanupVulkan();
}
