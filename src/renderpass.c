#include "device.h"
#include "error.h"
#include "swapchain.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

VkRenderPass renderPass = VK_NULL_HANDLE;

void createRenderPass() {
  VkAttachmentDescription colorAttachmentDescription = {
      .format = swapchainImageFormat,
      .samples = VK_SAMPLE_COUNT_1_BIT,
      .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
      .initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
      .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
  };

  VkAttachmentDescription attachments[] = {colorAttachmentDescription};

  VkAttachmentReference colorAttachmentReference = {
      .attachment = 0,
      .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
  };

  VkSubpassDescription subpassDescription[] = {{
      .colorAttachmentCount = 1,
      .pColorAttachments = &colorAttachmentReference,
  }};

  VkRenderPassCreateInfo renderPassCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
      .attachmentCount = sizeof(attachments) / sizeof(VkAttachmentDescription),
      .pAttachments = attachments,
      .subpassCount = sizeof(subpassDescription) / sizeof(VkSubpassDescription),
      .pSubpasses = subpassDescription,
  };
  EH(vkCreateRenderPass(device, &renderPassCreateInfo, nullptr, &renderPass));
}
