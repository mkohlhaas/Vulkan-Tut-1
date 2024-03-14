#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

const int WIDTH = 800;
const int HEIGHT = 600;

GLFWwindow *window;

static void error_callback(int error, const char *description) { fprintf(stderr, "GLFW Error: %s\n", description); }

// Press 'ESC' or 'Q' to exit
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// Sets `window` variable.
void initGlfw() {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Tutorial", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwSetKeyCallback(window, key_callback);
}

void cleanupGlfw() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void mainLoop() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
}
