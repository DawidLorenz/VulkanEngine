#include "main.hpp"

#include <vulkan/vulkan.h>

int main()
{
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = VK_APP_NAME;
    appInfo.pEngineName = VK_ENGINE_NAME;

    VkInstanceCreateInfo instatnceInfo = {};
    instatnceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instatnceInfo.pApplicationInfo = &appInfo;
 
    VkInstance instance = {};

    VkResult result = vkCreateInstance(&instatnceInfo, 0, &instance);
    if (result == VK_SUCCESS)
    {
        std::cout << "Successfully create vulkan instatnc\n";
    }
    std::cout << "Dawid Lorenz\n";
    return 0;
}