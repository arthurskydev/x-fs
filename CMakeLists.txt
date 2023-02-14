cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS 20)
set(CMAKE_CXX_COMPILE_FEATURES 20)
set(CMAKE_CXX_COMPILER_VERSION 20)

project(X-FS LANGUAGES CXX VERSION 2023.0.0)

add_subdirectory(examples)
add_subdirectory(X-FS)

configure_file(config.h.in ${CMAKE_BINARY_DIR}/config.h)
include_directories(${CMAKE_BINARY_DIR})
