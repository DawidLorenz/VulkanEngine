# VulkanEngine

# TODO
1) Change vcvars64.bat to CMake ?

# Setup
1) Change vcvars64.bat path in build.bat

# Step-By-Step how to Vulkan
1) Create VkInstanceCreateInfo
2) Create VkApplicationInfo and add to VkInstanceCreateInfo
3) Add Extension to VkInstanceCreateInfo
4) 

# Vulkan Knowledge
## Basic
A low-level, cross-platform, graphic and computing API.
- Vulkan is VERY verbose! Unline OpenGL, handles almost every individual GPU process manully
- Cross-platform (on Mac moltenvk METAL)
- online + offline
- Computing API, generic parallel programming tasks (like OpenCL)
- Vulkan API is much lower-lvl then OpenGL more control on GPU

## Instances, Devices and Validation Layers
### Instance
- Instancja Vulkan to odniesienie do kontekstu Vulkan. 
- Wszystkie aplikacje Vulkan zaczynają się od utworzenia instancji Vulkan 
- Instancja do uruchomienia Vulkan

### Physical Device vs Logical Device
- Physical Device its a GPU
- Logical Device its a interface to Physical Device

#### Physical Device (PD)
- Memory (data) allocate memory
- Queues, Process commands submitted to GPU in FIFO order
- do this by enumerating overl all devices and picking suitable.
- PD can have multiple type of queue.
- "Queue Families". Graphics, Compute, Transfer, or can be combination of theses

#### Logical Device (LD)
- Acts as an interface to the PD
- Will be referenced in a lot of Vulkan functions.
- Creation is relatively simple

### Extensions
- By default, Vulkan has no understand of what a "window" is. 
- GLFW (Graphic library framework)

### Validation Layers
- By default, Vulkan dosn't validate code. Will not report errors, and will simply crash if it encounters a fatal error.
- This is to avoid unnesessary overhead of error checking in release code
- Each "Layer" can check differenct functions

## Surfaces, Image Views and Swapchain

###