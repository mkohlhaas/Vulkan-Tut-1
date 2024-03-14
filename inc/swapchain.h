#include <vulkan/vulkan.h>

extern VkSwapchainKHR swapchain;
extern VkFormat imageFormat;
extern VkExtent2D swapchainExtent;
extern uint32_t swapchainImageCount;
extern VkImage *swapchainImages;

void createSwapchain();
