#include <stdio.h>
#include <vulkan/vulkan.h>

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

  char *msgType = messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT                  ? "General               "
                  : messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT             ? "Validation            "
                  : messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT            ? "Performance           "
                  : messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT ? "Device Address Binding"
                                                                                              : "                      ";

  fprintf(stderr, "Vulkan %s %s %s\n", msgSeverity, msgType, pCallbackData->pMessage);

  return VK_FALSE;
}

VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoEXT = {
    .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
    .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
    .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                   VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
    .pfnUserCallback = debugUtilsMessengerCB,
};
#endif

void initVulkan() {

  VkInstanceCreateInfo instanceCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
#ifndef NDEBUG
      .pNext = &debugUtilsMessengerCreateInfoEXT,
#endif
  };

  VkResult err = vkCreateInstance(&instanceCreateInfo, nullptr, &instance);

  switch (err) {
  VK_SUCCESS:
    fprintf(stderr, "Vulkan instance created!");
  VK_ERROR_OUT_OF_HOST_MEMORY:
    fprintf(stderr, "Error creating Vulkan instance: out of host memory");
  VK_ERROR_OUT_OF_DEVICE_MEMORY:
    fprintf(stderr, "Error creating Vulkan instance: out of device memory");
  VK_ERROR_INITIALIZATION_FAILED:
    fprintf(stderr, "Error creating Vulkan instance: initialization failed");
  VK_ERROR_LAYER_NOT_PRESENT:
    fprintf(stderr, "Error creating Vulkan instance: layer not present");
  VK_ERROR_EXTENSION_NOT_PRESENT:
    fprintf(stderr, "Error creating Vulkan instance: extension not present");
  VK_ERROR_INCOMPATIBLE_DRIVER:
    fprintf(stderr, "Error creating Vulkan instance: incompatible driver");
  };
}
