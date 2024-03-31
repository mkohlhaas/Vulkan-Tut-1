#pragma once

#define CGLM_FORCE_DEPTH_ZERO_TO_ONE

#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stdbool.h>

extern GLFWwindow *window;
extern bool framebufferResized;
extern bool isCameraMovingFwd;
extern bool isCameraMovingBwd;
extern bool isDragging;
// Shader mode (used in fragment shader).
extern uint32_t mode;
extern vec3 startMousePos;
extern vec3 currMousePos;

// Creates GLFW window.
void initGlfw();

// Polls events and draws frames.
void mainLoop();

// Destroys window and terminate GLFW.
void closeGlfw();

void updateCurrMousePos();

void updateStartMousePos();
