#include "cmdBuffer.h"
#include "device.h"
#include "instance.h"
#include "physical.h"
#include "pipeline.h"
#include "renderpass.h"
#include "surface.h"
#include "swapchain.h"
#include "sync.h"
#include "vertexBuffer.h"

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
  createVertexBuffer();
  createCmdBuffers();
  createSyncObjects();
}