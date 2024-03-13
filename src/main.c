#include "clean.h"
#include "instance.h"
#include "physical.h"
#include "window.h"

int main(void) {
  initGlfw();
  initVulkan();
#ifndef NDEBUG
  printPhysicalDevices();
#endif
  pickPhysicalDevice();
  mainLoop();
  cleanupVulkan();
}
