cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_COMPILER_VERSION 20)
set(CMAKE_CXX_EXTENSIONS  20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(X-FS LANGUAGES CXX VERSION 2023.0.0)

configure_file(config.h.in ${CMAKE_BINARY_DIR}/config.h)
include_directories(${CMAKE_BINARY_DIR})

add_library(${PROJECT_NAME} STATIC src/Engine.cpp src/Engine.h src/Engine.cpp src/Engine.h src/Engine.cpp src/Engine.h)
