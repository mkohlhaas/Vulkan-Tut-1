#pragma once

#include "close.h"
#include "vulkan.h"
#include "window.h"

void initialize() {
  initGlfw();
  initVulkan();
}

void shutdown() {
  closeVulkan();
  closeGlfw();
}
