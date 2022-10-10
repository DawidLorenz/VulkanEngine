#include "VulkanRenderer.h"
#include "../Utils/Logger.h"

VulkanRenderer::VulkanRenderer()
{
    
}

VulkanRenderer::~VulkanRenderer()
{

}

int VulkanRenderer::init(GLFWwindow * newWindow)
{
    window = newWindow;
 
    try {
        createInstance();
    } catch (const std::runtime_error &e) {
        VK_LOG_ERROR("ERROR: ", e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void VulkanRenderer::cleanup()
{
    vkDestroyInstance(instance, nullptr);
}

void VulkanRenderer::createInstance()
{   
    // Information abount the application itself
    // Most data here doesn't affect the program and is for developer convenience 
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan App"; // Custom name of the application
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0); // Custom version of the application
    appInfo.pEngineName = "No Engine"; // Custom engine name
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0); // Custom engine version
    appInfo.apiVersion = VK_API_VERSION_1_3; // Vulkan Version

    // Creation information for VkInstance (Vulkan instance)
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Create list to hold instance extension
    std::vector<const char*> instanceExtensions = std::vector<const char*>();

    // Setup extiosion use
    uint32_t glfwExtensionCount = 0; // GLFW may require multiple extension
    const char** gflwExtension; // Extensions passed as array so need pointer

    // Get GLFW extensions
    gflwExtension = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    // Add GLFW extenions to list of extensions
    for (size_t i = 0; i < glfwExtensionCount; i++)
    {
        instanceExtensions.push_back(gflwExtension[i]);
        VK_LOG_INFO("GLFW extension(", i, "): ", gflwExtension[i]);
    }

    // Check instance Extensions suported...
    if (!checkInstanceExtensionSupport(&instanceExtensions))
    {
        throw std::runtime_error("VkInstance does not support required extensions!");
    }

    createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
    createInfo.ppEnabledExtensionNames = instanceExtensions.data();


    // TODO: Set Validation layer the instance will use
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;

    // Create Instance
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Faild to create a Vulkan Instance!");
    }
}

bool VulkanRenderer::checkInstanceExtensionSupport(std::vector<const char*> * checkExtensions)
{
    // First teka number of extension to create array of correct size to hold extensions
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    // Create a list of VkExtensionProperties
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    // Check if given extension are in list of available extensions
    for (const auto &checkExtension :  *checkExtensions)
    {
        bool hasExtension = false;
        for (const auto &extension : extensions)
        {
            if (strcmp(checkExtension, extension.extensionName))
            {
                hasExtension = true;
                break;
            }
        }
        if (!hasExtension)
        {
            return false;
        }
    }

    return true;
}