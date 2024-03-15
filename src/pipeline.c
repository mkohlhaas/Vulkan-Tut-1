#include "device.h"
#include <vulkan/vulkan.h>

void createShaderModule(char *fileName) {
  VkShaderModuleCreateInfo createInfo;
  VkShaderModule shaderModule;
  vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule);
}

// VkDevice                                    device,
// const VkShaderModuleCreateInfo*             pCreateInfo,
// const VkAllocationCallbacks*                pAllocator,
// VkShaderModule*                             pShaderModule);
//
// VkShaderModuleCreateInfo {
//     VkStructureType              sType;
//     const void*                  pNext;
//     VkShaderModuleCreateFlags    flags;
//     size_t                       codeSize;
//     const uint32_t*              pCode;
