#pragma once

#include <GLFW/glfw3.h>

extern int width;
extern int height;

extern GLFWwindow *window;

// Destroys window and terminate GLFW.
void initGlfw();

// Polls events and draws frames.
void mainLoop();

// Closes window and terminates GLFW.
void cleanGlfw();
