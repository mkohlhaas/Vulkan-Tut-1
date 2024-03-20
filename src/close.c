#include "cmdBuffer.h"
#include "device.h"
#include "instance.h"
#include "pipeline.h"
#include "renderpass.h"
#include "surface.h"
#include "swapchain.h"
#include "sync.h"
#include "vertexBuffer.h"

void closeVulkan() {
  // device related objects
  closeSyncObjects();
  closeCmdBuffers();
  closeVertexBuffer();
  closeSwapchain();
  closePipeline();
  closeRenderPass();
  closeDevice();

  // instance related objects
  closeSurface();
  closeInstance();
}
