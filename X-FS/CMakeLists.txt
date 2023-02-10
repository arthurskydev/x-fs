cmake_minimum_required(VERSION 3.23)

add_subdirectory(src/X-FS)
add_subdirectory(vendor/yaml)

target_include_directories(${PROJECT_NAME} PUBLIC src/X-FS)

target_link_libraries(${PROJECT_NAME} yaml-cpp)

