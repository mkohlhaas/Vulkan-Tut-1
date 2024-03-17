#include "clean.h"
#include "vulkan.h"
#include "window.h"

void initialize() {
  initGlfw();
  initVulkan();
}

void cleanup() {
  cleanVulkan();
  cleanGlfw();
}
