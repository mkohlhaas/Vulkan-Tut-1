#include "cmdBuffer.h"
#include "descriptorSet.h"
#include "device.h"
#include "indexBuffer.h"
#include "instance.h"
#include "assets.h"
#include "physical.h"
#include "pipeline.h"
#include "renderpass.h"
#include "surface.h"
#include "swapchain.h"
#include "sync.h"
#include "uniformBuffers.h"
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
  createUniformBuffers();
  createDescriptorSets();
  createPipeline();
  createSwapchain();
  createCmdBuffers();
  loadAssets();
  createVertexBuffer();
  createIndexBuffer();
  createSyncObjects();
}

void closeVulkan() {
  deviceWaitIdle();

  // device related objects
  destroySyncObjects();
  destroyDescriptorSet();
  destroyUniformBuffers();
  destroyIndexBuffer();
  destroyVertexBuffer();
  unloadAssets();
  destroyCmdBuffers();
  destroySwapchain();
  destroyPipeline();
  destroyRenderPass();
  destroyDevice();

  // instance related objects
  destroySurface();
  destroyInstance();
}
