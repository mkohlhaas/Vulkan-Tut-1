#include "error.h"
#include "instance.h"
#include "surface.h"
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
uint32_t queueFamilyIndex = -1;

void printPhysicalDevices() {
  uint32_t physicalDeviceCount;
  EH(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr));

  if (!physicalDeviceCount) {
    dbgPrintExt("Failed to find GPUs with Vulkan support.");
    exit(EXIT_FAILURE);
  }

  VkPhysicalDevice physicalDevices[physicalDeviceCount];
  EH(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices));

  fprintf(stderr, "Physical Devices:\n");

  // loop over physical devices
  for (int i = 0; i < physicalDeviceCount; i++) {
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevices[i], &physicalDeviceProperties);
    fprintf(stderr, "  %d. %s\n", i + 1, physicalDeviceProperties.deviceName);

    fprintf(stderr, "     GPU available: %s\n",
            physicalDeviceProperties.deviceType &
                    (VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU | VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                ? "true"
                : "false");

    VkPhysicalDeviceFeatures physicalDeviceFeatures;
    vkGetPhysicalDeviceFeatures(physicalDevices[i], &physicalDeviceFeatures);
    fprintf(stderr, "     Geometry Shader available: %s\n", physicalDeviceFeatures.geometryShader ? "true" : "false");

    fprintf(stderr, "     Extensions:\n");
    uint32_t propertyCount;
    vkEnumerateDeviceExtensionProperties(physicalDevices[i], nullptr, &propertyCount, nullptr);
    VkExtensionProperties properties[propertyCount];
    vkEnumerateDeviceExtensionProperties(physicalDevices[i], nullptr, &propertyCount, properties);
    for (int i = 0; i < propertyCount; i++) {
      fprintf(stderr, "     %3d. %s\n", i + 1, properties[i].extensionName);
    }
  }
};

// We pick the first availabe graphics queue.
// Sets `physicalDevice` and `queueFamilyIndex` variables.
void pickPhysicalDevice() {
  uint32_t physicalDeviceCount;
  EH(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr));

  if (!physicalDeviceCount) {
    dbgPrintExt("Failed to find GPUs with Vulkan support.");
    exit(EXIT_FAILURE);
  }

  VkPhysicalDevice physicalDevices[physicalDeviceCount];
  EH(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices));

  // loop over physical devices
  for (int i = 0; i < physicalDeviceCount; i++) {
    // presentation support of queue family is mandatory (for our use case)
    VkBool32 presentSupport = VK_FALSE;
    vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevices[i], i, surface, &presentSupport);

    // check queue families
    uint32_t queueFamilyPropertyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[i], &queueFamilyPropertyCount, nullptr);

    // loop over queue families
    for (int j = 0; j < queueFamilyPropertyCount; j++) {
      VkQueueFamilyProperties queueFamilyProperties[queueFamilyPropertyCount];
      vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[i], &queueFamilyPropertyCount, queueFamilyProperties);

      if (presentSupport) {
        if (queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
          queueFamilyIndex = j;
          physicalDevice = physicalDevices[i];
          dbgPrint("We found a physical device and queue family with graphics and presentation support!\n");
          dbgPrint("  Device: %d\n  Queue Family: %d\n", i, j);
          break;
        }
      }
    }

    if (!physicalDevice) {
      fprintf(stderr, "No graphics queue available!\n");
      exit(EXIT_FAILURE);
    }
  }
};
