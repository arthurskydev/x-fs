cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)

project(X-FS LANGUAGES CXX VERSION 2023.0.0)

configure_file(config.h.in ${CMAKE_BINARY_DIR}/config.h)
include_directories(${CMAKE_BINARY_DIR})

add_library(${PROJECT_NAME} STATIC src/Engine.cpp src/Engine.h src/Engine.cpp src/Engine.h src/Engine.cpp src/Engine.h src/Aircraft.cpp src/Aircraft.h src/Math/Vec3.h)
