cmake_minimum_required(VERSION 3.27)

project(vktut VERSION 1.0 LANGUAGES C)

find_package(Vulkan    REQUIRED)
find_package(PkgConfig REQUIRED)

# Glib2
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
include_directories(${GLIB2_INCLUDE_DIRS})
link_directories(${GLIB2_LIBRARY_DIRS})
link_libraries(${GLIB2_LIBRARIES})

# cglm
add_subdirectory(3rdParty/cglm)

# stb - single-file public domain libraries for C/C++
include_directories(${PROJECT_SOURCE_DIR}/3rdParty/stb)
add_subdirectory(lib/stb)

# tinyobjloader-c
include_directories(${PROJECT_SOURCE_DIR}/3rdParty/tinyobjloader-c)
add_subdirectory(lib/tinyobjloader-c)

# GLFW
add_subdirectory(3rdParty/glfw)

add_executable(${PROJECT_NAME} src/main.c
                               src/buffer.c
                               src/cmdBuffer.c
                               src/depthBuffer.c
                               src/descriptorSet.c
                               src/device.c
                               src/draw.c
                               src/error.c
                               src/globals.c
                               src/image.c
                               src/instance.c
                               src/mesh.c
                               src/model.c
                               src/physical.c
                               src/pipeline.c
                               src/record.c
                               src/renderpass.c
                               src/surface.c
                               src/swapchain.c
                               src/sync.c
                               src/texture.c
                               src/trackball.c
                               src/uniformBuffers.c
                               src/vertexBuffer.c
                               src/view.c
                               src/vulkan.c
                               src/window.c)

target_link_libraries(${PROJECT_NAME} glfw cglm stb tinyobjloader-c Vulkan::Vulkan)
target_include_directories(${PROJECT_NAME} PRIVATE inc/)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 23)

file(GLOB_RECURSE GLSL_SOURCE_FILES
                  "shaders/*.frag"
                  "shaders/*.vert")

foreach(GLSL ${GLSL_SOURCE_FILES})
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${PROJECT_BINARY_DIR}/shaders/${FILE_NAME}.spv")
    add_custom_command(
      OUTPUT ${SPIRV}
      COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shaders/"
      COMMAND Vulkan::glslc ${GLSL} -o ${SPIRV} "$<$<CONFIG:Debug,RelWithDebInfo>:-g>"
      DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(Shaders DEPENDS ${SPIRV_BINARY_FILES})

add_dependencies(${PROJECT_NAME} Shaders)

add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                           ${CMAKE_CURRENT_SOURCE_DIR}/assets
                           ${CMAKE_CURRENT_BINARY_DIR}/assets)
