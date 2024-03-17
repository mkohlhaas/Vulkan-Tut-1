#pragma once

#include <vulkan/vulkan.h>
#include "types.h"

// Records commands into the command buffer.
void recordCmdBuffer(VkCommandBuffer, image_index);
