#include "cmdPool.h"
#include "device.h"
#include "instance.h"
#include "pipeline.h"
#include "renderpass.h"
#include "swapchain.h"
#include <vulkan/vulkan_core.h>
#include "framebuffer.h"
#include "surface.h"

void cleanVulkan() {
  // device related objects
  cleanCmdPool();
  cleanFramebuffers();
  cleanRenderPass();
  cleanPipeline();
  cleanSwapchain();
  cleanDevice();

  // instance related objects
  cleanSurface();
  cleanInstance();
}
