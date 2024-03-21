#include "texture.h"

static const char *textureFiles[] = {
    "assets/textures/texture.jpg",
};

enum { numTextures = sizeof(textureFiles) / sizeof(char *) };
static VkImage textureImage[numTextures];
static VkDeviceMemory textureImageMemory[numTextures];

static void loadTextures() {
  for (int i = 0; i < numTextures; i++) {
    createTextureImage(textureFiles[i], &textureImage[i], &textureImageMemory[i]);
  }
}

static void unloadTextures() {
  for (int i = 0; i < numTextures; i++) {
    destroyTextureImage(textureImage[i], textureImageMemory[i]);
  }
}

void loadAssets() { loadTextures(); }

void unloadAssets() { unloadTextures(); }
