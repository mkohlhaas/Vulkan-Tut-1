#define CGLM_FORCE_DEPTH_ZERO_TO_ONE

#include "draw.h"
#include "error.h"
#include "trackball.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  Shader_Phong,
  Shader_Toon,
  Shader_Constant,
  Shader_Count,
} ShaderMode;

// public variables
GLFWwindow *window;
bool framebufferResized = false;
ShaderMode mode = Shader_Phong;
bool isCameraMovingFwd = false;
bool isCameraMovingBwd = false;
bool isDragging = false;
vec3 startMousePos;
vec3 currMousePos;

// private variables
static int width = 800;
static int height = 600;

static void error_callback(int error, const char *description) { fprintf(stderr, "GLFW Error: %s\n", description); }

static void updateMousePos(vec3 mousePos) {
  double xpos;
  double ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  // project mouse coords
  mousePos[0] = xpos;
  mousePos[1] = ypos;
  mousePos[2] = 0.0f;
  projectMouseCoords(mousePos);
}

void updateCurrMousePos() { updateMousePos(currMousePos); }

void updateStartMousePos() { updateMousePos(startMousePos); }

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    dbgPrint("Left mouse button pressed!\n");
    isDragging = true;

    // record start mouse position and start time of rotation tracking
    updateStartMousePos();
  }
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    dbgPrint("Left mouse button released!\n");
    isDragging = false;
  }
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  // Press 'ESC' or 'Q' to exit application
  if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  } else {
    // Select shader mode
    if (key == GLFW_KEY_P && action == GLFW_PRESS) { // P = Phong Shader
      mode = Shader_Phong;
    } else if (key == GLFW_KEY_T && action == GLFW_PRESS) { // T = Toon Shader
      mode = Shader_Toon;
    } else if (key == GLFW_KEY_C && action == GLFW_PRESS) { // C = Constant Shader
      mode = Shader_Constant;
    } else if (key == GLFW_KEY_N && action == GLFW_PRESS) { // N → next shader
      mode++;
      mode = mode % Shader_Count;
    }

    // Camera movement
    if (key == GLFW_KEY_F && action == GLFW_PRESS) { // move camera towards center
      isCameraMovingFwd = true;
      isCameraMovingBwd = false;
    } else if (key == GLFW_KEY_B && action == GLFW_PRESS) { // move camera away from center
      isCameraMovingBwd = true;
      isCameraMovingFwd = false;
    } else if (key == GLFW_KEY_F && action == GLFW_RELEASE) { // move camera away from center
      isCameraMovingFwd = false;
    } else if (key == GLFW_KEY_B && action == GLFW_RELEASE) { // move camera away from center
      isCameraMovingBwd = false;
    }
  }
}

static void onResize(GLFWwindow *window, int width, int height) { framebufferResized = true; }

void initGlfw() {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  window = glfwCreateWindow(width, height, "Vulkan Tutorial", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetFramebufferSizeCallback(window, onResize);
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
}
