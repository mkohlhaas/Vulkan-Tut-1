#include "device.h"
#include "draw.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

GLFWwindow *window;
bool framebufferResized = false;

static int width = 800;
static int height = 600;

static void error_callback(int error, const char *description) { fprintf(stderr, "GLFW Error: %s\n", description); }

// Press 'ESC' or 'Q' to exit
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void onResize(GLFWwindow *window, int width, int height) { framebufferResized = true; }

void initGlfw() {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window = glfwCreateWindow(width, height, "Vulkan Tutorial", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwSetKeyCallback(window, key_callback);
  // glfwSetFramebufferSizeCallback(window, onResize);
}

void closeGlfw() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void mainLoop() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    drawFrame();
  }
  deviceWaitIdle();
}
