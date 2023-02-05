//
// Created by Arthur on 05.02.2023.
//

#ifndef X_FS_WINDOW_H
#define X_FS_WINDOW_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

namespace X_FS {
    class Window {
    public:
        Window();
        ~Window();

    private:
        GLFWwindow* m_Window = nullptr;
        VkInstance m_VkInstance{};
        VkDebugUtilsMessengerEXT m_DebugMessenger{};

    private:
        void createWindow();
        void destroyWindow();
        void loop();
        void initVulkan();

        void destroyVulkanItems();

        void setupDebugMessenger();
    };
}



#endif //X_FS_WINDOW_H
