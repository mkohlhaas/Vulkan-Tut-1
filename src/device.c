#include "error.h"
#include "physical.h"
#include <vulkan/vulkan.h>

VkDevice device = VK_NULL_HANDLE;
VkQueue graphicsQueue = VK_NULL_HANDLE;

// Creates a logical device.
// Sets `device` and `graphicsQueue` variables.
void createDevice() {
  float queuePriorities = 1.0f;
  VkDeviceQueueCreateInfo deviceQueueCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .queueFamilyIndex = queueFamilyIndex,
      .queueCount = 1,
      .pQueuePriorities = &queuePriorities,
  };

  VkDeviceCreateInfo createInfo = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .queueCreateInfoCount = 1,
      .pQueueCreateInfos = &deviceQueueCreateInfo,
  };
  EH(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device));

  vkGetDeviceQueue(device, queueFamilyIndex, 0, &graphicsQueue);
}
