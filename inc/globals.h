#pragma once

#include <stdint.h>

// Maximum frames in flight.
// TODO: Shouldn't this number be equal to the image views in the framebuffer?
// See `minImageCount` in swapchain.
#define MAX_FRAMES_IN_FLIGHT 2

// Current frame.
extern uint8_t currentFrame;
