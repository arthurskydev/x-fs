cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_COMPILER_VERSION 20)
set(CMAKE_CXX_EXTENSIONS  20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} src/main.cpp src/Window.cpp src/Window.h src/Sim.h src/Sim.cpp)

set(BUILD_SHARED_LIBS OFF)

add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/fmt)
add_subdirectory(vendor/glfw)

find_package(Vulkan REQUIRED FATAL_ERROR)


target_link_libraries(${PROJECT_NAME} ImGui)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog_header_only)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} fmt::fmt)
