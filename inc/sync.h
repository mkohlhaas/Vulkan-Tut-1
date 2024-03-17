#include <vulkan/vulkan.h>

extern VkSemaphore imageAvailableSemaphore;
extern VkSemaphore renderFinishedSemaphore;
extern VkFence inFlightFence;

void createSyncObjects();
void cleanSyncObjects();
