#include "vulkan.h"
#include "window.h"

// Start GLFW and Vulkan.
static void startup() {
  initGlfw();
  initVulkan();
}

// Shuts down GLFW and Vulkan.
static void shutdown() {
  closeVulkan();
  closeGlfw();
}
