#include "instance.h"

#ifndef NDEBUG
#include <GLFW/glfw3.h>
#include <stdio.h>

void destroyDebugMessenger() {
  PFN_vkDestroyDebugUtilsMessengerEXT destroyDebugUtilsMessenger =
      (PFN_vkDestroyDebugUtilsMessengerEXT)glfwGetInstanceProcAddress(instance, "vkDestroyDebugUtilsMessengerEXT");
  if (destroyDebugUtilsMessenger) {
    destroyDebugUtilsMessenger(instance, debugMessenger, nullptr);
  } else {
    fprintf(stderr, "Couldn't destroy debug messenger!\n");
  }
}
#endif

void cleanupVulkan() {
#ifndef NDEBUG
  destroyDebugMessenger();
#endif
  vkDestroyInstance(instance, nullptr);
}
