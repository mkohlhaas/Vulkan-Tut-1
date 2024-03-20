#pragma once

#include <bits/stdint-uintn.h>
#include <cglm/cglm.h>

typedef uint32_t image_index_t;


// Must match in draw() → VK_INDEX_TYPE_UINT16 !
// vkCmdBindIndexBuffer(cmdBuffers[currentFrame], indexBuffer, 0, VK_INDEX_TYPE_UINT16);
typedef uint16_t vertex_index_t;

typedef struct {
  vec2 pos;
  vec3 color;
} Vertex;
