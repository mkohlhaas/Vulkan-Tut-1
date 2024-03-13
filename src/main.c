#include "window.h"
#include "instance.h"

int main(void) {
  initGlfw();
  initVulkan();
  mainLoop();
}
