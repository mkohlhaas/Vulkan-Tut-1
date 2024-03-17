#include "cmdPool.h"
#include "device.h"
#include "framebuffer.h"
#include "instance.h"
#include "physical.h"
#include "pipeline.h"
#include "renderpass.h"
#include "surface.h"
#include "swapchain.h"

void initVulkan() {
  createInstance();
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
  createFramebuffers();
  createCommandPool();
  allocateCommandBuffer();
}
