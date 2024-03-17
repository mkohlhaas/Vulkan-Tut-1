#include "error.h"
#include "physical.h"
#include <vulkan/vulkan.h>

VkDevice device = VK_NULL_HANDLE;
VkQueue queue = VK_NULL_HANDLE;

// Creates a logical device.
// Sets `device` and `queue` variables.
void createDevice() {
  float queuePriorities = 1.0f;
  VkDeviceQueueCreateInfo deviceQueueCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .queueFamilyIndex = queueFamilyIndex,
      .queueCount = 1,
      .pQueuePriorities = &queuePriorities,
  };

  const char *const enabledExtensionNames = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

  VkDeviceCreateInfo createInfo = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .queueCreateInfoCount = 1,
      .pQueueCreateInfos = &deviceQueueCreateInfo,
      .enabledExtensionCount = 1,
      .ppEnabledExtensionNames = &enabledExtensionNames,
  };
  EH(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device));

  vkGetDeviceQueue(device, queueFamilyIndex, 0, &queue);
}

void cleanDevice() { vkDestroyDevice(device, nullptr); }
