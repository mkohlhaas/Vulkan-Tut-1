#include "error.h"
#include "instance.h"
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

void printPhysicalDevices() {
  uint32_t physicalDeviceCount;
  EH(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr));

  if (!physicalDeviceCount) {
    dbgPrintExt("Failed to find GPUs with Vulkan support.");
    exit(EXIT_FAILURE);
  }

  VkPhysicalDevice physicalDevices[physicalDeviceCount];
  EH(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices));

  fprintf(stderr, "Physical Devices\n");
  for (int i = 0; i < physicalDeviceCount; i++) {
    fprintf(stderr, "  %d. Physical Device\n", i + 1);
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevices[i], &physicalDeviceProperties);
    fprintf(stderr, "     GPU available: %s\n",
            physicalDeviceProperties.deviceType &
                    (VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU | VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                ? "true"
                : "false");
    VkPhysicalDeviceFeatures physicalDeviceFeatures;
    vkGetPhysicalDeviceFeatures(physicalDevices[i], &physicalDeviceFeatures);
    fprintf(stderr, "     Geometry Shader available: %s\n", physicalDeviceFeatures.geometryShader ? "true" : "false");
  }
};

// We pick the first availabe graphics queue.
// Sets `physicalDevice` variable.
void pickPhysicalDevice() {
  uint32_t physicalDeviceCount;
  EH(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr));

  if (!physicalDeviceCount) {
    dbgPrintExt("Failed to find GPUs with Vulkan support.");
    exit(EXIT_FAILURE);
  }

  VkPhysicalDevice physicalDevices[physicalDeviceCount];
  EH(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices));

  for (int i = 0; i < physicalDeviceCount; i++) {
    uint32_t queueFamilyPropertyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[i], &queueFamilyPropertyCount, nullptr);

    VkQueueFamilyProperties queueFamilyProperties[queueFamilyPropertyCount];
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[i], &queueFamilyPropertyCount, queueFamilyProperties);

    for (int i = 0; i < queueFamilyPropertyCount; i++) {
      if (queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
        physicalDevice = physicalDevices[i];
        dbgPrint("We found a physical device with graphics support!\n");
        break;
      }
    }
    if (!physicalDevice) {
      fprintf(stderr, "No graphics queue available!\n");
      exit(EXIT_FAILURE);
    }
  }
};
