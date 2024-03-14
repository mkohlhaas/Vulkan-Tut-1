# Vulkan Tutorial

## Window

### Commands

- Add [GLFW](https://www.glfw.org/) as a submodule:

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
- [Vulkan Dot File](https://github.com/mkohlhaas/Graphviz-Tutorial/blob/main/vulkan.svg)

### Key Functions
- glfwCreateWindow

## Instance

### Meaning

Open stateful Vulkan library.

### Key Functions

- vkCreateInstance
