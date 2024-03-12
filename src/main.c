#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

int main(void) {
  if (glfwInit()) {
    printf("GLFW is initialized!\n");
    if (glfwVulkanSupported()) {
      printf("Vulkan is minimally supported!\n");

      uint32_t count;
      const char **extensions = glfwGetRequiredInstanceExtensions(&count);

      if (extensions) {
        printf("Vulkan is fully supported!\n");
        glfwTerminate();
        exit(EXIT_SUCCESS);
      } else {
        printf("Vulkan is NOT fully supported!\n");
        glfwTerminate();
      }
    } else {
      printf("Vulkan is NOT supported!\n");
      glfwTerminate();
    }
  } else {
    printf("GLFW initialization failed!");
  }
  exit(EXIT_FAILURE);
}
