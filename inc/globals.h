#pragma once

#include "types.h"
#include <stdint.h>

// Maximum frames in flight.
#define MAX_FRAMES_IN_FLIGHT 2

// The current frame.
extern uint8_t currentFrame;

// The vertices.
extern const Vertex vertices[];

// Number of vertices.
extern size_t numVertices;

// The indices.
extern const vertex_index_t indices[];

// Number of indices.
extern size_t numIndices;
