#include "types.h"
#include <stdint.h>

uint8_t currentFrame = 0;

const const Vertex vertices[] = {{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
                                 {{+0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
                                 {{+0.5f, +0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
                                 {{-0.5f, +0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}};

size_t numVertices = sizeof(vertices) / sizeof(Vertex);

const vertex_index_t indices[] = {0, 1, 2, 2, 3, 0};

size_t numIndices = sizeof(indices) / sizeof(vertex_index_t);
