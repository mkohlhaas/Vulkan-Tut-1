#include "types.h"
#include <stdint.h>

uint8_t currentFrame = 0;

// vertices
const Vertex vertices[] = {{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
                           {{+0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
                           {{+0.5f, +0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
                           {{-0.5f, +0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

                           {{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
                           {{+0.5f, -0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
                           {{+0.5f, +0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
                           {{-0.5f, +0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}};

const size_t numVertices = sizeof(vertices) / sizeof(Vertex);

// indices
const uint16_t indices[] = {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4};

const size_t numIndices = sizeof(indices) / sizeof(vertex_index_t);
