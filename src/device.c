#include "error.h"
#include "physical.h"
#include <vulkan/vulkan.h>

VkDevice device = VK_NULL_HANDLE;
VkQueue queue = VK_NULL_HANDLE;

void createDevice() {
  float queuePriorities = 1.0f;
  VkDeviceQueueCreateInfo deviceQueueCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .queueFamilyIndex = getQueueFamilyIndex(),
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

  vkGetDeviceQueue(device, getQueueFamilyIndex(), 0, &queue);
}

VkQueue getDeviceQueue() { return queue; }

void deviceWaitIdle() { vkDeviceWaitIdle(device); }

void cleanDevice() { vkDestroyDevice(device, nullptr); }
