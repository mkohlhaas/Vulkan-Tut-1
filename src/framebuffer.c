#include "device.h"
#include "error.h"
#include "renderpass.h"
#include "swapchain.h"
#include <stdlib.h>
#include <vulkan/vulkan.h>

VkFramebuffer *swapchainFramebuffers;

void createFramebuffers() {
  swapchainFramebuffers = malloc(sizeof(VkFramebuffer) * swapchainImageCount);

  // TODO: is loop really necessary or can we just set attachmentCount ?
  for (int i = 0; i < swapchainImageCount; i++) {
    VkFramebufferCreateInfo framebufferCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        .renderPass = renderPass,
        .attachmentCount = 1,
        .pAttachments = swapchainImageViews,
        .width = swapchainExtent.width,
        .height = swapchainExtent.height,
        .layers = 1,
    };

    EH(vkCreateFramebuffer(device, &framebufferCreateInfo, nullptr, &swapchainFramebuffers[i]));
  }
}
