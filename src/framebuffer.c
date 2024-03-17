#include "device.h"
#include "error.h"
#include "renderpass.h"
#include "swapchain.h"
#include <stdlib.h>
#include <vulkan/vulkan.h>

VkFramebuffer *framebuffers;

void createFramebuffers() {
  framebuffers = malloc(sizeof(VkFramebuffer) * swapchainImagesCount);

  // TODO: is loop really necessary or can we just set attachmentCount ?
  for (int i = 0; i < swapchainImagesCount; i++) {
    VkFramebufferCreateInfo framebufferCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        .renderPass = renderPass,
        .attachmentCount = 1,
        .pAttachments = &swapchainImageViews[i],
        .width = swapchainExtent.width,
        .height = swapchainExtent.height,
        .layers = 1,
    };

    EH(vkCreateFramebuffer(device, &framebufferCreateInfo, nullptr, &framebuffers[i]));
  }
}

void cleanFramebuffers() {
  for (int i = 0; i < swapchainImagesCount; i++) {
    vkDestroyFramebuffer(device, framebuffers[i], nullptr);
  }
}
