#pragma once

#include <vulkan/vulkan_core.h>
#include <stdio.h>

extern VkResult err;

// Prints error message and exits application.
void handleError();

// EH - Error Handling
#define EH(c)                                                                                                          \
  err = c;                                                                                                             \
  handleError();

#ifdef NDEBUG
#define dbgPrint(fmt, ...)
#else
#define dbgPrint(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__);
#endif

#ifdef NDEBUG
#define dbgPrintExt(fmt, ...)
#else
#define dbgPrintExt(fmt, ...) fprintf(stderr, fmt " in file %s (line %d)\n", ##__VA_ARGS__, __FILE__, __LINE__);
#endif

#define log(fmt, ...) fprintf(stderr, fmt " in file %s (line %d)\n", ##__VA_ARGS__, __FILE__, __LINE__);
