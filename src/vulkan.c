#include "cmdBuffer.h"
#include "depthBuffer.h"
#include "descriptorSet.h"
#include "device.h"
#include "instance.h"
#include "mesh.h"
#include "model.h"
#include "physical.h"
#include "pipeline.h"
#include "renderpass.h"
#include "surface.h"
#include "swapchain.h"
#include "trackball.h"
#include "sync.h"
#include "uniformBuffers.h"
#include "vertexBuffer.h"

const char *modelFile = "assets/models/monkey.obj";

void initVulkan() {
  loadModelMatrix();
  loadQuat();
  loadMesh(modelFile);
  createInstance();
  createSurface();
#ifndef NDEBUG
  printPhysicalDevices();
#endif
  pickPhysicalDevice();
  createDevice();
  createSwapchain();
  createDepthImage();
  createRenderPass();
  createFramebuffers();
  createUniformBuffers();
  createCmdBuffers();
  createDescriptorSets();
  createPipeline();
  createVertexBuffer();
  createSyncObjects();
}

void closeVulkan() {
  deviceWaitIdle();

  // device related objects
  destroySyncObjects();
  destroyDescriptorSet();
  destroyCmdBuffers();
  destroyUniformBuffers();
  destroyVertexBuffer();
  destroyDepthImage();
  destroySwapchain();
  destroyPipeline();
  destroyRenderPass();
  destroyDevice();

  // instance related objects
  destroySurface();
  destroyInstance();
}
