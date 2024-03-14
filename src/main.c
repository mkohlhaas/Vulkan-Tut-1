#include "clean.h"
#include "device.h"
#include "instance.h"
#include "physical.h"
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
  createSwapchain();
  mainLoop();
  cleanupVulkan();
}
