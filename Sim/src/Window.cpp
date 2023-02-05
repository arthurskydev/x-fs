//
// Created by Arthur on 05.02.2023.
//

#include "Window.h"
#include "config.h"
#include "spdlog/spdlog.h"
#include <vector>


//
// -- Constants
//

const std::vector<const char *> c_ValidationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

//
// -- Vulkan Helpers
//

void CheckVKResult(VkResult err) {
    if (err != 0) {
        throw std::runtime_error("Received VkResult");
    }
}

void AssertInstanceExtensionsValid(const std::vector<const char *> &requestedExtension) {
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

    std::vector<const char *> extensionNames(availableExtensions.size());

    for (const auto &extensionToCheck: requestedExtension) {
        bool found;
        for (const auto &extension: availableExtensions) {
            auto cleanName = strstr(extensionToCheck, extension.extensionName);
            if (cleanName != nullptr) {
                found = true;
                break;
            }
        }

        if (!found) {
            throw std::runtime_error(fmt::format("VkInstanceExtension {} not supported", extensionToCheck));
        }
    }
}

bool CheckValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char *layerName: c_ValidationLayers) {
        bool layerFound = false;

        for (const auto &layerProperties: availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}

std::vector<const char *> GetRequiredExtensions(bool enableValidationLayers) {
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    AssertInstanceExtensionsValid(extensions);

    return extensions;
}

#define log(func) \
    func("[Vulkan] {}", pCallbackData->pMessage)

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
        void *pUserData) {


    if ((messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) != 0) {
        log(spdlog::debug);
    }
    if ((messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) != 0) {
        log(spdlog::info);
    }
    if ((messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) != 0) {
        log(spdlog::warn);
    }
    if ((messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) != 0) {
        log(spdlog::error);
    } else {
        log(spdlog::info);
    }

    return VK_FALSE;
}

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *pAllocator,
                                      VkDebugUtilsMessengerEXT *pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity =
            // VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
    createInfo.pUserData = nullptr; // Optional
}

///
/// -- Window-class implementation
///
namespace X_FS {
    Window::Window() {
        createWindow();
        initVulkan();
        setupDebugMessenger();
        loop();
    }

    Window::~Window() {
        destroyVulkanItems();
        destroyWindow();
    }

    void Window::createWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_Window = glfwCreateWindow(800, 600, fmt::format("{} Version {}", PROJECT_NAME, PROJECT_VER).c_str(), nullptr,
                                    nullptr);
    }

    void Window::destroyWindow() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Window::loop() {
        while (!glfwWindowShouldClose(m_Window)) {
            glfwPollEvents();
        }
    }

    void Window::initVulkan() {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = PROJECT_NAME;
        appInfo.applicationVersion = VK_MAKE_VERSION(std::stoi(PROJECT_VER_MAJOR), std::stoi(PROJECT_VER_MINOR),
                                                     std::stoi(PROJECT_VER_PATCH));
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        bool validationLayersEnabled = false;

#ifndef NDEBUG
        if (!CheckValidationLayerSupport()) {
            spdlog::warn("Validation layers are not supported");
            createInfo.enabledLayerCount = 0;

        } else {
            validationLayersEnabled = true;
            createInfo.enabledLayerCount = static_cast<uint32_t>(c_ValidationLayers.size());
            createInfo.ppEnabledLayerNames = c_ValidationLayers.data();
        }
#else
        createInfo.enabledLayerCount = 0;
#endif

        auto glfwExtensions = GetRequiredExtensions(validationLayersEnabled);

        createInfo.enabledExtensionCount = static_cast<uint32_t>(glfwExtensions.size());
        createInfo.ppEnabledExtensionNames = glfwExtensions.data();

        VkDebugUtilsMessengerCreateInfoEXT messengerCreateInfo{};
        PopulateDebugMessengerCreateInfo(messengerCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *) &messengerCreateInfo;

        CheckVKResult(vkCreateInstance(&createInfo, nullptr, &m_VkInstance));
    }

    void Window::setupDebugMessenger() {
        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        PopulateDebugMessengerCreateInfo(createInfo);
        CheckVKResult(CreateDebugUtilsMessengerEXT(m_VkInstance, &createInfo, nullptr, &m_DebugMessenger));
    }

    void Window::destroyVulkanItems() {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(m_VkInstance,
                                                                                "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(m_VkInstance, m_DebugMessenger, nullptr);
        }
        vkDestroyInstance(m_VkInstance, nullptr);
    }
}

