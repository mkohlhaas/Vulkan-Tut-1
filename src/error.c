#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan_core.h>

VkResult err;

static void _handleError(const char *fileName, int lineNumber) {
  if (err) {
    switch (err) {
    case VK_SUCCESS:
      fprintf(stderr, "Vulkan Success: but still exiting! This should never happen!");
      break;
    case VK_NOT_READY:
      fprintf(stderr, "Vulkan Error: not ready");
      break;
    case VK_TIMEOUT:
      fprintf(stderr, "Vulkan Error: timeout");
      break;
    case VK_EVENT_SET:
      fprintf(stderr, "Vulkan Error: event set");
      break;
    case VK_EVENT_RESET:
      fprintf(stderr, "Vulkan Error: event reset");
      break;
    case VK_INCOMPLETE:
      fprintf(stderr, "Vulkan Error: incomplete");
      break;
    case VK_ERROR_OUT_OF_HOST_MEMORY:
      fprintf(stderr, "Vulkan Error: out of host memory");
      break;
    case VK_ERROR_OUT_OF_DEVICE_MEMORY:
      fprintf(stderr, "Vulkan Error: out of device memory");
      break;
    case VK_ERROR_INITIALIZATION_FAILED:
      fprintf(stderr, "Vulkan Error: initialization failed");
      break;
    case VK_ERROR_DEVICE_LOST:
      fprintf(stderr, "Vulkan Error: device lost");
      break;
    case VK_ERROR_MEMORY_MAP_FAILED:
      fprintf(stderr, "Vulkan Error: memory map failed");
      break;
    case VK_ERROR_LAYER_NOT_PRESENT:
      fprintf(stderr, "Vulkan Error: layer not present");
      break;
    case VK_ERROR_EXTENSION_NOT_PRESENT:
      fprintf(stderr, "Vulkan Error: extension not present");
      break;
    case VK_ERROR_FEATURE_NOT_PRESENT:
      fprintf(stderr, "Vulkan Error: feature not present");
      break;
    case VK_ERROR_INCOMPATIBLE_DRIVER:
      fprintf(stderr, "Vulkan Error: incompatible driver");
      break;
    case VK_ERROR_TOO_MANY_OBJECTS:
      fprintf(stderr, "Vulkan Error: too many objects");
      break;
    case VK_ERROR_FORMAT_NOT_SUPPORTED:
      fprintf(stderr, "Vulkan Error: format not supported");
      break;
    case VK_ERROR_FRAGMENTED_POOL:
      fprintf(stderr, "Vulkan Error: fragmented pool");
      break;
    case VK_ERROR_UNKNOWN:
      fprintf(stderr, "Vulkan Error: unknown");
      break;
    case VK_ERROR_OUT_OF_POOL_MEMORY:
      fprintf(stderr, "Vulkan Error: out of pool memory");
      break;
    case VK_ERROR_INVALID_EXTERNAL_HANDLE:
      fprintf(stderr, "Vulkan Error: invalid external handle");
      break;
    case VK_ERROR_FRAGMENTATION:
      fprintf(stderr, "Vulkan Error: fragmentation");
      break;
    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
      fprintf(stderr, "Vulkan Error: invalid opaque capture address");
      break;
    case VK_PIPELINE_COMPILE_REQUIRED:
      fprintf(stderr, "Vulkan Error: pipeline compile required");
      break;
    case VK_ERROR_SURFACE_LOST_KHR:
      fprintf(stderr, "Vulkan Error: surface lost");
      break;
    case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
      fprintf(stderr, "Vulkan Error: native window in use");
      break;
    case VK_SUBOPTIMAL_KHR:
      fprintf(stderr, "Vulkan Error: suboptimal");
      break;
    case VK_ERROR_OUT_OF_DATE_KHR:
      fprintf(stderr, "Vulkan Error: out of date");
      break;
    case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
      fprintf(stderr, "Vulkan Error: incompatible display");
      break;
    case VK_ERROR_VALIDATION_FAILED_EXT:
      fprintf(stderr, "Vulkan Error: validation failed");
      break;
    case VK_ERROR_INVALID_SHADER_NV:
      fprintf(stderr, "Vulkan Error: invalid shader");
      break;
    case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR:
      fprintf(stderr, "Vulkan Error: image usage not supported");
      break;
    case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR:
      fprintf(stderr, "Vulkan Error: video picture layout not supported");
      break;
    case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR:
      fprintf(stderr, "Vulkan Error: video profile operation not supported");
      break;
    case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR:
      fprintf(stderr, "Vulkan Error: video profile format not supported");
      break;
    case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR:
      fprintf(stderr, "Vulkan Error: video profile codec not supported");
      break;
    case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR:
      fprintf(stderr, "Vulkan Error: video std version not supported");
      break;
    case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
      fprintf(stderr, "Vulkan Error: invalid drm format modifier plane layout");
      break;
    case VK_ERROR_NOT_PERMITTED_KHR:
      fprintf(stderr, "Vulkan Error: not permitted");
      break;
    case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
      fprintf(stderr, "Vulkan Error: full screen exclusive mode lost");
      break;
    case VK_THREAD_IDLE_KHR:
      fprintf(stderr, "Vulkan Error: thread idle");
      break;
    case VK_THREAD_DONE_KHR:
      fprintf(stderr, "Vulkan Error: thread done");
      break;
    case VK_OPERATION_DEFERRED_KHR:
      fprintf(stderr, "Vulkan Error: operation deferred");
      break;
    case VK_OPERATION_NOT_DEFERRED_KHR:
      fprintf(stderr, "Vulkan Error: operation not deferred");
      break;
    case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR:
      fprintf(stderr, "Vulkan Error: invalid video std parameters");
      break;
    case VK_ERROR_COMPRESSION_EXHAUSTED_EXT:
      fprintf(stderr, "Vulkan Error: compression exhausted");
      break;
    case VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT:
      fprintf(stderr, "Vulkan Error: incompatible shader binary");
      break;
    case VK_RESULT_MAX_ENUM:
      fprintf(stderr, "Vulkan Error: result max enum");
      break;
    };
    fprintf(stderr, " in file %s, line %d, error code %d\n", fileName, lineNumber, err);
    exit(EXIT_FAILURE);
  };
}

void handleError() { _handleError(__FILE__, __LINE__); }
