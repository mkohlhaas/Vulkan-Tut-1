#include "error.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vulkan/vulkan_core.h>

VkInstance instance;

#ifndef NDEBUG
static VkBool32 debugUtilsMessengerCB(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                      VkDebugUtilsMessageTypeFlagsEXT messageTypes,
                                      const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData) {
  char *msgSeverity = messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT   ? "Verbose"
                      : messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT    ? "Info   "
                      : messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT ? "Warning"
                      : messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT   ? "Error  "
                                                                                          : "       ";

  char *msgType = messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT       ? "General               "
                  : messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT  ? "Validation            "
                  : messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT ? "Performance           "
                  : messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT
                      ? "Device Address Binding"
                      : "                      ";

  fprintf(stderr, "Vulkan %s %s %s\n", msgSeverity, msgType, pCallbackData->pMessage);
  return VK_FALSE;
}

static VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoEXT = {
    .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
    .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
    .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                   VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
    .pfnUserCallback = debugUtilsMessengerCB,
};

static void printRequiredGlfwExtensions(const char **glfwExtensions, uint32_t glfwExtensionCount) {
  fprintf(stderr, "Required GLFW extensions\n");
  for (int i = 0; i < glfwExtensionCount; i++) {
    fprintf(stderr, "%3d: %s\n", i + 1, glfwExtensions[i]);
  }
}

static void printInstanceExtensions() {
  uint32_t propertyCount;
  EH(vkEnumerateInstanceExtensionProperties(nullptr, &propertyCount, nullptr));
  VkExtensionProperties properties[propertyCount];
  EH(vkEnumerateInstanceExtensionProperties(nullptr, &propertyCount, properties));

  fprintf(stderr, "Instance Extensions\n");
  for (int i = 0; i < propertyCount; i++) {
    fprintf(stderr, "%3d: %s\n", i + 1, properties[i].extensionName);
  };
}

#endif

void initVulkan() {
  dbgPrint("Initializing Vulkan…\n");

  // by GLFW required extensions
  uint32_t glfwExtensionCount;
  const char **glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
  if (!glfwExtensions) {
    fprintf(stderr, "GLFW Error: %s in line %d\n", __FILE__, __LINE__);
  }

#ifndef NDEBUG
  printRequiredGlfwExtensions(glfwExtensions, glfwExtensionCount);
  printInstanceExtensions();
#endif

  // create Vulkan instance
  VkApplicationInfo applicationInfo = {
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .apiVersion = VK_API_VERSION_1_3,
  };

  VkInstanceCreateInfo instanceCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .enabledExtensionCount = glfwExtensionCount,
      .ppEnabledExtensionNames = glfwExtensions,
      .pApplicationInfo = &applicationInfo,
#ifndef NDEBUG
      .pNext = &debugUtilsMessengerCreateInfoEXT,
#endif
  };

  EH(vkCreateInstance(&instanceCreateInfo, nullptr, &instance));

  dbgPrint("Vulkan instance created!\n");
}
