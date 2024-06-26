#include "error.h"
#include "tinyobj_loader_c.h"
#include "types.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

Vertex *vertices;
size_t numVertices;

static char *mmap_file(const char *filename, size_t *len) {
  {
    char *p = nullptr;

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
      logExit("`open` failed");
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
      logExit("`fstat` failed");
    }

    if (!S_ISREG(sb.st_mode)) {
      logExit("%s is not a file", filename);
    }

    p = (char *)mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);

    if (p == MAP_FAILED) {
      logExit("`mmap` failed");
    }

    if (close(fd) == -1) {
      logExit("`close` failed");
    }

    *len = sb.st_size;

    return p;
  }
}

static void get_file_data(void *ctx, const char *filename, const int is_mtl, const char *obj_filename, char **data,
                          size_t *len) {
  dbgPrint("File name: %s\n", filename);
  dbgPrint("Is material file: %s\n", is_mtl ? "true" : "false");
  dbgPrint("Obj file name: %s\n", obj_filename);

  if (!filename) {
    logExit("No obj filename for mesh data given.");
  }

  *data = mmap_file(filename, len);
}

bool loadMesh(const char *filename) {
  tinyobj_attrib_t attrib;
  tinyobj_shape_t *shapes = nullptr;
  size_t num_shapes;
  tinyobj_material_t *_materials = nullptr;
  size_t _num_materials;

  {
    // load object file into mapped memory
    int ret = tinyobj_parse_obj(&attrib, &shapes, &num_shapes, &_materials, &_num_materials, filename, get_file_data,
                                nullptr, TINYOBJ_FLAG_TRIANGULATE);
    if (ret != TINYOBJ_SUCCESS) {
      logError("Couldn't load mesh data from obj file %s.", filename);
      return false;
    }

    // print number of shapes and material
    dbgPrint("# of shapes    = %zu\n", num_shapes);
    dbgPrint("# of materials = %zu\n", _num_materials);
    dbgPrint("# of indices   = %u\n", attrib.num_faces);

#ifndef NDEBUG
    // print shape names
    for (int i = 0; i < num_shapes; i++) {
      fprintf(stderr, "shape[%d] name = %s\n", i, shapes[i].name);
    }
#endif
  }

  {

    numVertices = attrib.num_faces;
    dbgPrint("Number of vertices: %zu\n", numVertices);
    dbgPrint("Number of faces: %u\n", attrib.num_faces);
    dbgPrint("Number of faces num verts: %u\n", attrib.num_face_num_verts);
    dbgPrint("Number of normals: %u\n", attrib.num_normals);

    if (!attrib.num_normals) {
      logExit("Object does not contain normals information. Please do a proper export!");
    }

    vertices = malloc(numVertices * sizeof(Vertex));
    if (!vertices) {
      logExit("Not enough memory");
    }

    // normals
    for (int i = 0; i < attrib.num_faces; i++) {
      dbgPrint("Index: %d\n", attrib.faces[i].v_idx);
      vertices[i].pos[0] = *(attrib.vertices + 3 * attrib.faces[i].v_idx + 0);
      vertices[i].pos[2] = *(attrib.vertices + 3 * attrib.faces[i].v_idx + 1);
      vertices[i].pos[1] = *(attrib.vertices + 3 * attrib.faces[i].v_idx + 2);
      vertices[i].normal[0] = *(attrib.normals + 3 * attrib.faces[i].vn_idx + 0);
      vertices[i].normal[2] = *(attrib.normals + 3 * attrib.faces[i].vn_idx + 1);
      vertices[i].normal[1] = *(attrib.normals + 3 * attrib.faces[i].vn_idx + 2);
      dbgPrint("vertex %4d normal x: %f\n", i, vertices[i].normal[0]);
      dbgPrint("            normal y: %f\n", vertices[i].normal[2]);
      dbgPrint("            normal z: %f\n", vertices[i].normal[1]);
    }
  }

  return true;
}
