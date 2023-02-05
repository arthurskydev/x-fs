cmake_minimum_required(VERSION 3.14)

add_subdirectory(vendor/imgui)
add_subdirectory(vendor/spdlog)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} spdlog)