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
      .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
      .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
      .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
      .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
  };

  VkAttachmentDescription attachments[] = {colorAttachmentDescription};

  VkAttachmentReference colorAttachmentReference = {
      .attachment = 0,
      .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
  };

  VkSubpassDescription subpassDescription[] = {{
      .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
      .colorAttachmentCount = 1,
      .pColorAttachments = &colorAttachmentReference,
  }};

  VkSubpassDependency dependency = {
      .srcSubpass = VK_SUBPASS_EXTERNAL,
      .dstSubpass = 0,
      .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
      .srcAccessMask = 0,
      .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
      .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
  };

  VkRenderPassCreateInfo renderPassCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
      .attachmentCount = sizeof(attachments) / sizeof(VkAttachmentDescription),
      .pAttachments = attachments,
      .subpassCount = sizeof(subpassDescription) / sizeof(VkSubpassDescription),
      .pSubpasses = subpassDescription,
      .dependencyCount = 1,
      .pDependencies = &dependency,
  };
  EH(vkCreateRenderPass(device, &renderPassCreateInfo, nullptr, &renderPass));
}

void closeRenderPass() { vkDestroyRenderPass(device, renderPass, nullptr); }
