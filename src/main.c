#include <stdlib.h>
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

void initGlfw();
void mainLoop();

int main(void) {
  initGlfw();
  mainLoop();
}
