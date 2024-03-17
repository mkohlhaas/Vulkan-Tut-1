#include "device.h"
#include "error.h"
#include "renderpass.h"
#include "swapchain.h"
#include <stdlib.h>
#include <vulkan/vulkan.h>

VkFramebuffer *framebuffers;

void createFramebuffers() {
  framebuffers = malloc(sizeof(VkFramebuffer) * getSwapchainImageCount());

  // TODO: is loop really necessary or can we just set attachmentCount ?
  for (int i = 0; i < getSwapchainImageCount(); i++) {
    VkFramebufferCreateInfo framebufferCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        .renderPass = renderPass,
        .attachmentCount = 1,
        .pAttachments = getSwapchainImageViews(),
        .width = getSwapchainExtent().width,
        .height = getSwapchainExtent().height,
        .layers = 1,
    };

    EH(vkCreateFramebuffer(device, &framebufferCreateInfo, nullptr, &framebuffers[i]));
  }
}

void cleanFramebuffers() {
  for (int i = 0; i < getSwapchainImageCount(); i++) {
    vkDestroyFramebuffer(device, framebuffers[i], nullptr);
  }
}
