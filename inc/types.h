#pragma once

#include <bits/stdint-uintn.h>
#include <cglm/cglm.h>

typedef uint32_t image_index_t;

typedef struct {
  vec3 pos;
  vec3 normal;
} Vertex;

typedef struct {
  alignas(16) mat4 model;
  alignas(16) mat4 view;
  alignas(16) mat4 proj;
} UniformBufferObject;
