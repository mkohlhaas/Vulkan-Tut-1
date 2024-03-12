cmake_minimum_required(VERSION 3.27)

project(vktut VERSION 1.0 LANGUAGES C)

find_package(Vulkan REQUIRED)

add_subdirectory(glfw)

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} glfw Vulkan::Vulkan)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 23)
