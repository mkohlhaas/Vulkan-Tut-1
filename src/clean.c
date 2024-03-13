#include "instance.h"

void cleanupVulkan() { vkDestroyInstance(instance, nullptr); }
