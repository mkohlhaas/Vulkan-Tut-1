#include "cmdBuffer.h"
#include "descriptorSet.h"
#include "error.h"
#include "globals.h"
#include "mesh.h"
#include "pipeline.h"
#include "renderpass.h"
#include "swapchain.h"
#include "types.h"
#include "vertexBuffer.h"
#include "window.h"
#include <stdint.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

static void beginCmdBuffer() {
  VkCommandBufferBeginInfo commandBufferBeginInfo = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
      .flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
  };
  EH(vkBeginCommandBuffer(cmdBuffers[currentFrame], &commandBufferBeginInfo));
}

static void beginRenderPass(image_index_t imageIndex) {
  // renderPass → colorAttachmentDescription → loadOp
  const VkClearColorValue colorClearValue = {0.03f, 0.03f, 0.03f, 1.0f};
  const VkClearValue clearValues[] = {
      {.color = {{0.02f, 0.02f, 0.02f, 1.0f}}},
      {.depthStencil = {1.0f, 0}},
  };

  VkRenderPassBeginInfo renderPassBeginInfo = {
      .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
      .renderPass = renderPass,
      .framebuffer = framebuffers[imageIndex],
      .renderArea = {{0, 0}, swapchainExtent},
      .clearValueCount = sizeof(clearValues) / sizeof(VkClearValue),
      .pClearValues = clearValues,
  };
  vkCmdBeginRenderPass(cmdBuffers[currentFrame], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
}

static void bindPipeline() { vkCmdBindPipeline(cmdBuffers[currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline); }

// Dynamic States in pipeline
static void setViewport() {
  VkViewport viewport = {0.0f, 0.0f, swapchainExtent.width, swapchainExtent.height, 0.0f, 1.0f};
  vkCmdSetViewport(cmdBuffers[currentFrame], 0, 1, &viewport);
}

static void setScissor() {
  VkRect2D scissor = {{0.0f, 0.0f}, swapchainExtent};
  vkCmdSetScissor(cmdBuffers[currentFrame], 0, 1, &scissor);
}

// static void draw() { vkCmdDrawIndexed(cmdBuffers[currentFrame], numIndices, 1, 0, 0, 0); }

static void draw() { vkCmdDraw(cmdBuffers[currentFrame], numVertices, 1, 0, 0); }

static void endRenderPass() { vkCmdEndRenderPass(cmdBuffers[currentFrame]); }

static void endCmdBuffer() { EH(vkEndCommandBuffer(cmdBuffers[currentFrame])); }

static void bindBuffers() {
  // bind vertex buffer
  VkBuffer vertexBuffers[] = {vertexBuffer};
  uint32_t numBindings = sizeof(vertexBuffers) / sizeof(VkBuffer);
  VkDeviceSize offsets[] = {0};
  vkCmdBindVertexBuffers(cmdBuffers[currentFrame], 0, numBindings, vertexBuffers, offsets);

  // bind uniform object buffer
  vkCmdBindDescriptorSets(cmdBuffers[currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1,
                          &descriptorSets[currentFrame], 0, nullptr);

  // push constants
  vkCmdPushConstants(cmdBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(uint32_t),
                     &mode);
}

void recordCmdBuffer(image_index_t imageIndex) {
  beginCmdBuffer();
  beginRenderPass(imageIndex);
  bindPipeline();
  setViewport();
  setScissor();
  bindBuffers();
  draw();
  endRenderPass();
  endCmdBuffer();
}
