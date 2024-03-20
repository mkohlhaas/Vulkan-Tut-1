#include "error.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vulkan/vulkan_core.h>

VkInstance instance = VK_NULL_HANDLE;

#ifndef NDEBUG
#include <stdlib.h>
#include <string.h>

VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;

static const char *requiredValidationLayers[] = {"VK_LAYER_KHRONOS_validation" /* bundle of validation layers */};

// print debug messages to console
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

static const VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoEXT = {
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

static void printAvailableInstanceExtensions() {
  uint32_t propertyCount;
  EH(vkEnumerateInstanceExtensionProperties(nullptr, &propertyCount, nullptr));
  VkExtensionProperties properties[propertyCount];
  EH(vkEnumerateInstanceExtensionProperties(nullptr, &propertyCount, properties));

  fprintf(stderr, "Instance Extensions\n");
  for (int i = 0; i < propertyCount; i++) {
    fprintf(stderr, "%3d: %s\n", i + 1, properties[i].extensionName);
  };
}

static void printAvailableInstanceLayers() {
  uint32_t propertyCount;
  EH(vkEnumerateInstanceLayerProperties(&propertyCount, nullptr));
  VkLayerProperties properties[propertyCount];
  EH(vkEnumerateInstanceLayerProperties(&propertyCount, properties));

  fprintf(stderr, "Instance Layers\n");
  for (int i = 0; i < propertyCount; i++) {
    fprintf(stderr, "%3d: %s (%s)\n", i + 1, properties[i].layerName, properties[i].description);
  };
}

// Sets `debugMessenger` variable.
static void createDebugMessenger() {
  PFN_vkCreateDebugUtilsMessengerEXT createDebugUtilsMessenger =
      (PFN_vkCreateDebugUtilsMessengerEXT)glfwGetInstanceProcAddress(instance, "vkCreateDebugUtilsMessengerEXT");
  if (createDebugUtilsMessenger) {
    EH(createDebugUtilsMessenger(instance, &debugUtilsMessengerCreateInfoEXT, nullptr, &debugMessenger));
  } else {
    fprintf(stderr, "Couldn't create debug messenger!\n");
    exit(EXIT_FAILURE);
  }
}

#endif

// Open Vulkan library.
// Sets `instance` variable.
void createInstance() {
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
  printAvailableInstanceExtensions();
  printAvailableInstanceLayers();
#endif

  // create Vulkan instance
  VkApplicationInfo applicationInfo = {
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .apiVersion = VK_API_VERSION_1_3,
      .pApplicationName = "Vulkan Tutorial",
      .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
      .pEngineName = "No Engine",
      .engineVersion = VK_MAKE_VERSION(1, 0, 0),
  };

#ifndef NDEBUG
  const char *requiredExtensions[glfwExtensionCount + 1];
  memcpy(requiredExtensions, glfwExtensions, glfwExtensionCount * sizeof(char *));
  requiredExtensions[glfwExtensionCount] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME; // debug messages for all messages
  VkInstanceCreateInfo instanceCreateInfo = {
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .enabledExtensionCount = glfwExtensionCount + 1,
    .ppEnabledExtensionNames = requiredExtensions,
    .pApplicationInfo = &applicationInfo,
    .pNext = &debugUtilsMessengerCreateInfoEXT, // debug messages during Vulkan startup and shutdown
    .enabledLayerCount = sizeof(requiredValidationLayers) / sizeof(char *),
    .ppEnabledLayerNames = requiredValidationLayers,
#else
  VkInstanceCreateInfo instanceCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .enabledExtensionCount = glfwExtensionCount,
      .ppEnabledExtensionNames = glfwExtensions,
      .pApplicationInfo = &applicationInfo,
#endif
  };

  EH(vkCreateInstance(&instanceCreateInfo, nullptr, &instance));

  dbgPrint("Vulkan instance created!\n");

#ifndef NDEBUG
  createDebugMessenger();
#endif
}

#ifndef NDEBUG
static void destroyDebugMessenger() {
  PFN_vkDestroyDebugUtilsMessengerEXT destroyDebugUtilsMessenger =
      (PFN_vkDestroyDebugUtilsMessengerEXT)glfwGetInstanceProcAddress(instance, "vkDestroyDebugUtilsMessengerEXT");
  if (destroyDebugUtilsMessenger) {
    destroyDebugUtilsMessenger(instance, debugMessenger, nullptr);
  } else {
    fprintf(stderr, "Couldn't destroy debug messenger!\n");
  }
}
#endif

void closeInstance() {
#ifndef NDEBUG
  destroyDebugMessenger(); // just before destroying the instance itself
#endif
  vkDestroyInstance(instance, nullptr);
}
