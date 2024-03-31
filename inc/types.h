#pragma once

#define CGLM_FORCE_DEPTH_ZERO_TO_ONE

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
  alignas(16) vec4 light;
} UniformBufferObject;

// typedef enum {
//   Dragging_Start,
//   Dragging,
//   // Dragging_Stop,
// } DraggingMode;
