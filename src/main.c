#include "window.h"
#include "clean.h"
#include "instance.h"

int main(void) {
  initGlfw();
  initVulkan();
  mainLoop();
  cleanupVulkan();
}
