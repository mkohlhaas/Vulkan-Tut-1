#include "texture.h"

//////////////
// Textures //
//////////////

static const char *textureFiles[] = {
    "assets/textures/texture.jpg",
};

enum { numTextures = sizeof(textureFiles) / sizeof(char *) };

static VkImage textureImage[numTextures];
static VkDeviceMemory textureImageMemory[numTextures];
static VkImageView textureImageView[numTextures];
static VkSampler textureSampler;

static void loadTextures() {
  for (int i = 0; i < numTextures; i++) {
    createTextureImage(textureFiles[i], &textureImage[i], &textureImageView[i], &textureImageMemory[i]);
  }
}

static void unloadTextures() {
  for (int i = 0; i < numTextures; i++) {
    destroyTextureImage(textureImage[i], textureImageView[i], textureImageMemory[i]);
  }
}

void loadAssets() {
  createTextureSampler(&textureSampler);
  loadTextures();
}

void unloadAssets() {
  destroyTextureSampler(textureSampler);
  unloadTextures();
}
