# Vulkan Tutorial

### Add [GLFW](https://www.glfw.org/) as a Submodule

```shell
git submodule add https://github.com/glfw/glfw.git
git checkout -b 3.4                                  # check out latest release (3.4)
git config submodule.glfw.ignore all                 # freeze repository
git config --list --local                            # check settings
```

### Links

- GLFW
  - [Building with CMake and GLFW source](https://www.glfw.org/docs/latest/build_guide.html#build_link_cmake_source)
  - [Vulkan guide](https://www.glfw.org/docs/3.3/vulkan_guide.html)
  - [Putting it together](https://www.glfw.org/docs/3.3/quick_guide.html#quick_example)
  - [Example code](https://www.glfw.org/documentation.html)
  - [Window size & resize](https://www.glfw.org/docs/3.3/window_guide.html#window_size)
- [Vulkan SVG File](https://github.com/mkohlhaas/Graphviz-Tutorial/blob/main/vulkan.svg)
- YT [Vulkan Lecture Series](https://www.youtube.com/watch?v=tLwbj9qys18&list=PLmIqTlJ6KsE1Jx5HV4sd2jOe3V1KMHHgn)
  - Vulkan Essentials             (First Steps as Vulkan Developer)
  - Swap Chain                    (Presentation Modes and Swap Chain Setup in Vulkan)
  - Resources & Descriptors       (Use Buffers and Images in Vulkan Shaders)
  - Commands and Command Buffers  (Submit Work to a Device⧸GPU)
  - Pipelines and Stages          (Inside Graphics, Compute, Ray Tracing Pipes)
  - Real-Time Ray Tracing         (RTX ON in Vulkan)
  - Vulkan Synchronization        (Understand Fences, Semaphores, Barriers,…)
- Renderpass YT Videos
  - [Render Passes in Vulkan](https://www.youtube.com/watch?v=x2SGVjlVGhE)
  - [Deferred Shading](https://www.youtube.com/watch?v=6Qnv7jssdYc)
- [Graphics Pipeline](https://vulkan-tutorial.com/images/vulkan_simplified_pipeline.svg)
- [GLSL docs](https://docs.gl/#)
- [Layout Qualifier (GLSL)](https://www.khronos.org/opengl/wiki/Layout_Qualifier_(GLSL))
- [Normalized Device Coordinates in Vulkan(NDC)](https://vulkan-tutorial.com/images/normalized_device_coordinates.svg)
- Semaphores (*GPU*)
  - Semaphores are used both to order work inside the same queue and between different queues.
  - Two kinds of semaphores in Vulkan, `binary` and `timeline`.
  - Semaphores are used to specify the execution order of operations on the GPU
- Fences (*CPU*, *GPU*)
  - A fence is for ordering the execution on the *CPU*. If the host needs to know when the GPU has finished something, we use a fence.
  - Fences are used to keep the CPU and GPU in sync with each-other.
- [Vulkan Memory Allocator](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator)
- [c-api for imgui](https://github.com/cimgui/cimgui)
- [Unveiling the Power of Anonymous Functions in C](https://medium.com/@future_fanatic/unveiling-the-power-of-anonymous-functions-in-c-a-guide-to-cleaner-code-4ffc76b2ce07)
- [Deletion queue](https://vkguide.dev/docs/chapter-2/cleanup/)
- Dynamic Rendering:
  - [VK_KHR_dynamic_rendering tutorial](https://lesleylai.info/en/vk-khr-dynamic-rendering/)
  - [Vulkan dynamic rendering](https://quadbit.medium.com/vulkan-dynamic-rendering-f993a9a8ca58)
  - [Vulkan Dynamic Rendering](https://www.ultraengine.com/community/blogs/entry/2743-vulkan-dynamic-rendering/)
- [Frame profiler](https://github.com/wolfpld/tracy)
- [Simple stupid SVG parser](https://github.com/memononen/nanosvg)
- [YT: Common Mistakes When Learning Vulkan](https://www.youtube.com/watch?v=0OqJtPnkfC8&t=17s&pp=ygUWY29tbW9uIG1pc3Rha2VzIHZ1bGthbg%3D%3D)
- [YT: Using Vulkan Configurator for Daily Vulkan development](https://www.youtube.com/watch?v=T0oN_H2avnI&pp=ygUZdXNpbmcgdnVsa2FuIGNvbmZpZ3VyYXRvcg%3D%3D)
- [YT: Using Vulkan Validation Effectively](https://www.youtube.com/watch?v=FA-3tmKT9TE&pp=ygUXdXNpbmcgdnVsa2FuIHZhbGlkYXRpb24%3D)
