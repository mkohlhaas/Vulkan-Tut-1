#pragma once

#include <vulkan/vulkan.h>

extern VkSemaphore imageAvailableSemaphore[];
extern VkSemaphore renderFinishedSemaphore[];
extern VkFence inFlightFence[];

// Creates synchronization objects.
void createSyncObjects();

// Destroys synchronization objects.
void destroySyncObjects();
