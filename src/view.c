#define CGLM_FORCE_DEPTH_ZERO_TO_ONE

#include "window.h"
#include <cglm/cglm.h>

// view matrix
mat4 viewMatrix;

void updateViewMatrix() {
  static vec3 eye = {0.0f, 2.0f, 0.0f};
  static vec3 center = {0.0f, 0.0f, 0.0f};
  static vec3 up = {0.0f, 0.0f, 1.0f};
  static float stepSize = 0.001f;

  if (isCameraMovingFwd || isCameraMovingBwd) {
    stepSize *= 1.04f;
  } else {
    stepSize = 0.001f;
  }

  if (isCameraMovingFwd && eye[1] > 1.3f) {
    eye[1] -= stepSize;
  } else if (isCameraMovingBwd && eye[1] < 5.0f) {
    eye[1] += stepSize;
  }

  glm_lookat(eye, center, up, (vec4 *)&viewMatrix);
}
