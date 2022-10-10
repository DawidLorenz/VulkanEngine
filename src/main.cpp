#define GLFW_INCLUDE_VULKAN

#include "render/VulkanRenderer.h"
#include "Utils/Profiler.h"
#include "Utils/Logger.h"

#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <iostream>

GLFWwindow * window;
VulkanRenderer vulkanRenderer;

void initWindow(std::string wName = "Test Window", 
                const int width = 800,
                const int height = 600)
{
  // Init GLFW
  glfwInit();

  // Set GLFW to NOT work with OpenGL
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
}

int main(int argc, char** argv)
{
  VK_PROFILE_BEGIN_SESSION("VK_ENGINE", "Result.json");

  // Create Window
  initWindow("Test Window", 800, 600);

  // Create Vulkan Renderer instance
  if (vulkanRenderer.init(window) == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }

  // Loop until closed
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
  }
  
  vulkanRenderer.cleanup();

  // Destroy GLFW window and stop GLFW
  glfwDestroyWindow(window);
  glfwTerminate();

  VK_PROFILE_END_SESSION();
  return EXIT_SUCCESS;
}