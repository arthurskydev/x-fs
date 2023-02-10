cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(examples)
add_subdirectory(vendor/json)

project(X-FS LANGUAGES CXX VERSION 2023.0.0)

configure_file(config.h.in ${CMAKE_BINARY_DIR}/config.h)
include_directories(${CMAKE_BINARY_DIR})

add_library(${PROJECT_NAME} STATIC X-FS/src/Engine.cpp X-FS/src/Engine.h X-FS/src/Engine.cpp X-FS/src/Engine.h X-FS/src/Engine.cpp X-FS/src/Engine.h X-FS/src/Aircraft/Aircraft.cpp X-FS/src/Aircraft/Aircraft.h X-FS/src/Vec3.h examples/main.cpp include/X-FS/Core.h)

target_link_libraries(${PROJECT_NAME} nlohmann_json)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE X-FS/src)
