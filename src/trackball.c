#include "cglm/quat.h"
#define CGLM_FORCE_DEPTH_ZERO_TO_ONE

#include "error.h"
#include "swapchain.h"
#include "trackball.h"
#include "window.h"
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <sys/param.h>

// constants
static const float radius = 1.0f;

// public variables
versor currQ;

void loadQuat() { glm_quat_identity(currQ); }

void projectMouseCoords(vec3 coords) {
  uint32_t res = MIN(swapchainExtent.width, swapchainExtent.height) - 1;

  // calculate x, y → project coords to canonical (-1, +1)
  float x = (2 * coords[0] - swapchainExtent.width - 1) / res;
  float y = (2 * coords[1] - swapchainExtent.height - 1) / res;

  // calculate z
  float z;
  float d = x * x + y * y;
  if (2 * d <= radius * radius) {
    z = sqrt(radius * radius - d);
  } else {
    z = radius * radius / 2 / sqrt(d); // smooth out with hyperbolic function
  }

  ((float *)coords)[0] = x;
  ((float *)coords)[2] = y;
  ((float *)coords)[1] = z;
  glm_vec3_normalize(coords);
}

void draggingQuat() {
  updateCurrMousePos();
  dbgPrint("mouse %f %f %f\r", currMousePos[0], currMousePos[1], currMousePos[2]);
  glm_quat_from_vecs(startMousePos, currMousePos, currQ);
  glm_quat_conjugate(currQ, currQ);
  glm_vec3_copy(currMousePos, startMousePos);
}

void slidingQuat() {
  vec3 axis;
  glm_quat_axis(currQ, axis);
  float angle = glm_quat_angle(currQ);
  angle *= 0.993f;
  dbgPrint("angle: %f\r", angle);
  // only angle of rotation changes for quaternion
  glm_quatv(currQ, angle, axis);
}
