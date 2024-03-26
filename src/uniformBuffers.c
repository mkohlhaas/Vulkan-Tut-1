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

VkBuffer uniformBuffers[FRAMES_IN_FLIGHT];
VkDeviceMemory uniformBuffersMemory[FRAMES_IN_FLIGHT];
void *uniformBuffersMapped[FRAMES_IN_FLIGHT];

void createUniformBuffers() {
  VkDeviceSize bufferSize = sizeof(UniformBufferObject);

  VkBufferUsageFlags usages = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
  VkMemoryPropertyFlags props = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

  for (size_t i = 0; i < FRAMES_IN_FLIGHT; i++) {
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
  vec3 axis = {0.0f, 0.0f, 1.0f};
  glm_rotate(model, elapsedTime * glm_rad(90.0f / 2.0f), axis);

  // view matrix
  mat4 view;
  vec3 eye = {2.0f, 2.0f, 1.5f};
  vec3 center = {0.0f, 0.0f, 0.0f};
  vec3 up = {0.0f, 0.0f, 1.0f};
  glm_lookat(eye, center, up, (vec4 *)&view);

  // projection matrix
  mat4 proj;
  glm_perspective(glm_rad(45.0f), (float)swapchainExtent.width / swapchainExtent.height, 0.1f, 10.0f, (vec4 *)&proj);
  proj[1][1] *= -1;

  // light
  mat4 light;
  vec3 translate = {1.0f, 0.0f, 0.0f};
  glm_mat4_identity(light);
  glm_translate(light, translate);

  glm_mat4_print(model, stderr);
  glm_mat4_print(view, stderr);
  glm_mat4_print(proj, stderr);
  glm_mat4_print(light, stderr);

  // uniform buffer object
  UniformBufferObject ubo;
  glm_mat4_copy(model, ubo.model);
  glm_mat4_copy(view, ubo.view);
  glm_mat4_copy(proj, ubo.proj);
  glm_mat4_copy(light, ubo.light);

  memcpy(uniformBuffersMapped[currentFrame], &ubo, sizeof(ubo));
}

void destroyUniformBuffers() {
  for (int i = 0; i < FRAMES_IN_FLIGHT; i++) {
    destroyBuffer(uniformBuffers[i], uniformBuffersMemory[i]);
  }
}
