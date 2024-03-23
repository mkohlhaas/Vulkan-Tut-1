#pragma once

#include <bits/stdint-uintn.h>
#include <cglm/cglm.h>

typedef uint32_t image_index_t;

// Must match in draw() → VK_INDEX_TYPE_UINT16 !
// vkCmdBindIndexBuffer(cmdBuffers[currentFrame], indexBuffer, 0, VK_INDEX_TYPE_UINT16);
typedef uint16_t vertex_index_t;

typedef struct {
  vec3 pos;
  vec3 color;
  vec2 texCoord;
} Vertex;

typedef struct {
  alignas(16) mat4 model;
  alignas(16) mat4 view;
  alignas(16) mat4 proj;
} UniformBufferObject;
