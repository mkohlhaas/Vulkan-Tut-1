#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan_core.h>

extern VkResult err;

// Prints error or warning message and exits application in case of error.
void handleError(const char *fileName, int lineNumber);

// EH - Error Handling
#define EH(c)                                                                                                          \
  err = c;                                                                                                             \
  handleError(__FILE__, __LINE__);

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

// Logs error to stderr.
#define logError(fmt, ...) fprintf(stderr, fmt " in file %s (line %d)\n", ##__VA_ARGS__, __FILE__, __LINE__);

// Logs error to stderr and exits.
#define logExit(fmt, ...)                                                                                              \
  fprintf(stderr, fmt " in file %s (line %d)\n", ##__VA_ARGS__, __FILE__, __LINE__);                                   \
  exit(EXIT_FAILURE);
