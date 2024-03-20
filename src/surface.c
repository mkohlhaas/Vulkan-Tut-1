#include "error.h"
#include "instance.h"
#include "window.h"
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

VkSurfaceKHR surface;

void createSurface() { EH(glfwCreateWindowSurface(instance, window, nullptr, &surface)); }

void closeSurface() { vkDestroySurfaceKHR(instance, surface, nullptr); }
