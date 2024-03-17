#include "cmdPool.h"
#include "device.h"
#include "framebuffer.h"
#include "instance.h"
#include "pipeline.h"
#include "renderpass.h"
#include "surface.h"
#include "swapchain.h"
#include "sync.h"
#include <vulkan/vulkan_core.h>

void cleanVulkan() {
  // device related objects
  cleanCmdBuffer();
  cleanFramebuffers();
  cleanRenderPass();
  cleanPipeline();
  cleanSwapchain();
  cleanSyncObjects();
  cleanDevice();

  // instance related objects
  cleanSurface();
  cleanInstance();
}
