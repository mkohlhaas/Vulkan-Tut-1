#pragma once

#define CGLM_FORCE_DEPTH_ZERO_TO_ONE

#include "types.h"
#include <cglm/cglm.h>

extern vec3 startMousePos;
extern double startTime;
extern versor currQ;

// Projects mouse coordinates to canonical coordinates (-1, +1).
void projectMouseCoords(vec3 coords);

// Calculates quaternion while dragging.
void draggingQuat();

// Calculates quaternion while sliding.
void slidingQuat();

// Loads initial quaternion.
void loadQuat();
