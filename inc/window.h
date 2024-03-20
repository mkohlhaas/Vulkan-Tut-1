#pragma once

#include <GLFW/glfw3.h>

extern GLFWwindow *window;
extern bool framebufferResized;

// Destroys window and terminate GLFW.
void initGlfw();

// Polls events and draws frames.
void mainLoop();

// Closes window and terminates GLFW.
void closeGlfw();
