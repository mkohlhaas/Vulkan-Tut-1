#pragma once

#include <GLFW/glfw3.h>
#include <stdbool.h>

extern GLFWwindow *window;
extern bool framebufferResized;

// Creates GLFW window.
void initGlfw();

// Polls events and draws frames.
void mainLoop();

// Destroys window and terminate GLFW.
void closeGlfw();
