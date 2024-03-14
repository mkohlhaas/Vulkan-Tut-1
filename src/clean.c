#include "device.h"
#include "instance.h"
#include "surface.h"
#include "swapchain.h"
#include <vulkan/vulkan_core.h>

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

  ////////////////////////////////////
  // destroy device related objects //
  ////////////////////////////////////

  vkDestroySwapchainKHR(device, swapchain, nullptr);
  vkDestroyDevice(device, nullptr);

  //////////////////////////////////////
  // destroy instance related objects //
  //////////////////////////////////////

  vkDestroySurfaceKHR(instance, surface, nullptr);
#ifndef NDEBUG
  destroyDebugMessenger(); // just before destroying the instance itself
#endif
  vkDestroyInstance(instance, nullptr);
}
