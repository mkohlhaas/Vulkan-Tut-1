#define CGLM_FORCE_DEPTH_ZERO_TO_ONE

#include "buffer.h"
#include "device.h"
#include "error.h"
#include "globals.h"
#include "swapchain.h"
#include "types.h"
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <string.h>
#include <vulkan/vulkan.h>

VkBuffer uniformBuffers[MAX_FRAMES_IN_FLIGHT];
VkDeviceMemory uniformBuffersMemory[MAX_FRAMES_IN_FLIGHT];
void *uniformBuffersMapped[MAX_FRAMES_IN_FLIGHT];

void createUniformBuffers() {
  VkDeviceSize bufferSize = sizeof(UniformBufferObject);

  VkBufferUsageFlags usages = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
  VkMemoryPropertyFlags props = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    createBuffer(bufferSize, usages, props, &uniformBuffers[i], &uniformBuffersMemory[i]);
    EH(vkMapMemory(device, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]));
  }
}

void updateUniformBuffer(uint32_t currentFrame) {
  double elapsedTime = glfwGetTime();
  dbgPrint("Elapsed time = %f seconds\r", elapsedTime);

  // model matrix
  mat4 model;
  glm_mat4_identity(model);
  vec3 v1 = {0.0f, 0.0f, 1.0f};
  glm_rotate(model, elapsedTime * glm_rad(90.0f / 2.0f), v1);

  // view matrix
  vec3 v2 = {2.0f, 2.0f, 2.0f};
  vec3 v3 = {0.0f, 0.0f, 0.0f};
  vec3 v4 = {0.0f, 0.0f, 1.0f};
  mat4 view;
  glm_lookat(v2, v3, v4, (vec4 *)&view);

  // projection matrix
  mat4 proj;
  glm_perspective(glm_rad(45.0f), (float)swapchainExtent.width / swapchainExtent.height, 0.1f, 10.0f, (vec4 *)&proj);

  glm_mat4_print(model, stderr);
  glm_mat4_print(view, stderr);
  glm_mat4_print(proj, stderr);

  // uniform buffer object
  UniformBufferObject ubo;

  glm_mat4_copy(model, ubo.model);
  glm_mat4_copy(view, ubo.view);
  glm_mat4_copy(proj, ubo.proj);

  memcpy(uniformBuffersMapped[currentFrame], &ubo, sizeof(ubo));
}

void destroyUniformBuffers() {
  for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    destroyBuffer(uniformBuffers[i], uniformBuffersMemory[i]);
  }
}
