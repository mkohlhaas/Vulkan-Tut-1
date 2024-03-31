#pragma once

#define CGLM_FORCE_DEPTH_ZERO_TO_ONE

#include <cglm/cglm.h>

extern mat4 modelMatrix;

// Initializes model matrix.
void loadModelMatrix();

// Updates model matrix (local to world coordinates).
void updateModelMatrix();
