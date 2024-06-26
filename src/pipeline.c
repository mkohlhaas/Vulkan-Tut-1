#include "descriptorSet.h"
#include "device.h"
#include "error.h"
#include "renderpass.h"
#include "types.h"
#include <stdint.h>
#include <glib.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

VkPipeline pipeline = VK_NULL_HANDLE;
VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;

static char *vertexShaderFilename = "shaders/shader.vert.spv";
static char *fragmentShaderFilename = "shaders/shader.frag.spv";

static gboolean readFile(const char *filename, gchar **contents, gsize *len) {
  return g_file_get_contents(filename, contents, len, nullptr);
}

static VkShaderModule createShaderModule(char *fileName) {

  // load vertex shader from file
  gchar *shaderCode;
  gsize lenShaderCode;
  if (!readFile(fileName, &shaderCode, &lenShaderCode)) {
    logExit("SPIR-v file %s not found", fileName);
  }

  dbgPrint("Code size %s: %lu\n", fileName, lenShaderCode);
  if (lenShaderCode % 4) {
    logExit("Shader code %s has incorrect size", fileName);
  }

  VkShaderModuleCreateInfo createInfo = {
      .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
      .codeSize = lenShaderCode,
      .pCode = (const uint32_t *)shaderCode,
  };
  VkShaderModule shaderModule;
  EH(vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule));
  return shaderModule;
}

void createPipeline() {
  // Shader Stages
  VkShaderModule vertShaderModule = createShaderModule(vertexShaderFilename);
  VkShaderModule fragShaderModule = createShaderModule(fragmentShaderFilename);

  VkPipelineShaderStageCreateInfo vertexPipelineShaderStageCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage = VK_SHADER_STAGE_VERTEX_BIT,
      .module = vertShaderModule,
      .pName = "main",
  };

  VkPipelineShaderStageCreateInfo fragmentPipelineShaderStageCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
      .module = fragShaderModule,
      .pName = "main",
  };

  VkPipelineShaderStageCreateInfo shaderStages[] = {vertexPipelineShaderStageCreateInfo,
                                                    fragmentPipelineShaderStageCreateInfo};

  // Pipeline Layout (uniform & push values)
  VkDescriptorSetLayout descriptorSetLayouts[] = {descriptorSetLayout};
  VkPushConstantRange pushConstantRanges[] = {{VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(int32_t)}};

  VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
      .setLayoutCount = sizeof(descriptorSetLayouts) / sizeof(VkDescriptorSetLayout),
      .pSetLayouts = descriptorSetLayouts,
      .pushConstantRangeCount = sizeof(pushConstantRanges) / sizeof(VkPushConstantRange),
      .pPushConstantRanges = pushConstantRanges,
  };

  EH(vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout));

  // Multisampling
  VkPipelineMultisampleStateCreateInfo multisampling = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
      .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
  };

  VkPipelineDepthStencilStateCreateInfo depthStencil = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
      .depthTestEnable = VK_TRUE,
      .depthWriteEnable = VK_TRUE,
      .depthCompareOp = VK_COMPARE_OP_LESS,
  };

  // Vertex Input
  VkVertexInputBindingDescription bindingDescriptions[] = {{
      .binding = 0,
      .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
      .stride = sizeof(Vertex),
  }};
  VkVertexInputAttributeDescription attributeDescriptions[] = {
      {
          .binding = 0,
          .location = 0,
          .format = VK_FORMAT_R32G32B32_SFLOAT,
          .offset = offsetof(Vertex, pos),
      },
      {
          .binding = 0,
          .location = 1,
          .format = VK_FORMAT_R32G32B32_SFLOAT,
          .offset = offsetof(Vertex, normal),
      },
  };

  VkPipelineVertexInputStateCreateInfo vertexInput = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
      .vertexBindingDescriptionCount = sizeof(bindingDescriptions) / sizeof(VkVertexInputBindingDescription),
      .pVertexBindingDescriptions = bindingDescriptions,
      .vertexAttributeDescriptionCount = sizeof(attributeDescriptions) / sizeof(VkVertexInputAttributeDescription),
      .pVertexAttributeDescriptions = attributeDescriptions,
  };

  // Input Assembly
  VkPipelineInputAssemblyStateCreateInfo inputAssembly = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
      .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
  };

  // Dynamic States
  const VkDynamicState dynamicStates[] = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};

  VkPipelineDynamicStateCreateInfo viewportDynamicState = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
      .dynamicStateCount = sizeof(dynamicStates) / sizeof(VkDynamicState),
      .pDynamicStates = dynamicStates,
  };

  VkPipelineViewportStateCreateInfo viewportState = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
      .viewportCount = 1,
      .scissorCount = 1,
  };

  // Rasterizer
  VkPipelineRasterizationStateCreateInfo rasterizationState = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
      .polygonMode = VK_POLYGON_MODE_FILL,
      .cullMode = VK_CULL_MODE_NONE,
      .frontFace = VK_FRONT_FACE_CLOCKWISE,
      .lineWidth = 1.0f,
  };

  // Color Blending
  VkPipelineColorBlendAttachmentState colorBlendAttachment = {
      .colorWriteMask =
          VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
      .blendEnable = VK_TRUE,
      .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
      .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
      .colorBlendOp = VK_BLEND_OP_ADD,
      .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
      .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
      .alphaBlendOp = VK_BLEND_OP_ADD,
  };

  VkPipelineColorBlendStateCreateInfo colorBlendState = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
      .attachmentCount = 1,
      .pAttachments = &colorBlendAttachment,
      .blendConstants = {},
  };

  VkGraphicsPipelineCreateInfo createInfo = {
      .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
      .stageCount = sizeof(shaderStages) / sizeof(VkPipelineShaderStageCreateInfo),
      .pStages = shaderStages,
      .pVertexInputState = &vertexInput,
      .pInputAssemblyState = &inputAssembly,
      .pViewportState = &viewportState,
      .pRasterizationState = &rasterizationState,
      .pMultisampleState = &multisampling,
      .pDepthStencilState = &depthStencil,
      .pColorBlendState = &colorBlendState,
      .pDynamicState = &viewportDynamicState,
      .layout = pipelineLayout,
      .renderPass = renderPass,
  };
  EH(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &createInfo, nullptr, &pipeline));

  vkDestroyShaderModule(device, fragShaderModule, nullptr);
  vkDestroyShaderModule(device, vertShaderModule, nullptr);
}

void destroyPipeline() {
  vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
  vkDestroyPipeline(device, pipeline, nullptr);
}
