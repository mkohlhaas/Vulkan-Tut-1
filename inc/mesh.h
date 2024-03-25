#pragma once

#include "types.h"

extern Vertex *vertices;
extern size_t numVertices;
extern vertex_index_t *indices;
extern size_t numIndices;

// Fills `vertices` and `indices`.
bool loadMesh(const char *filename);
