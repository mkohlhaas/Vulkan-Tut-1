#include "clean.h"
#include "device.h"
#include "instance.h"
#include "physical.h"
#include "window.h"
#include "surface.h"

int main(void) {
  initGlfw();
  initVulkan();
  createSurface();
#ifndef NDEBUG
  printPhysicalDevices();
#endif
  pickPhysicalDevice();
  createDevice();
  mainLoop();
  cleanupVulkan();
}
