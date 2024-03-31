#define CGLM_FORCE_DEPTH_ZERO_TO_ONE

#include "trackball.h"
#include "window.h"
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <sys/param.h>

// public
mat4 modelMatrix;

void loadModelMatrix() { glm_mat4_identity(modelMatrix); }

void updateModelMatrix() {
  switch (isDragging) {
  case true:
    draggingQuat();
    break;
  case false:
    slidingQuat();
    break;
  }
  glm_quat_rotate(modelMatrix, currQ, modelMatrix);
}
