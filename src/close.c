#include "cmdBuffer.h"
#include "device.h"
#include "instance.h"
#include "pipeline.h"
#include "renderpass.h"
#include "surface.h"
#include "swapchain.h"
#include "sync.h"
#include <vulkan/vulkan_core.h>

void closeVulkan() {
  // device related objects
  closeCmdBuffers();
  closeRenderPass();
  closePipeline();
  closeSwapchain();
  closeSyncObjects();
  closeDevice();

  // instance related objects
  closeSurface();
  closeInstance();
}
