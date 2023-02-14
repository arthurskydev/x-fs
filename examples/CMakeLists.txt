cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS 20)
set(CMAKE_CXX_COMPILE_FEATURES 20)

project(X-FS-Example)

add_executable(${PROJECT_NAME} main.cpp ../X-FS/src/X-FS/X-FS.h)

target_link_libraries(${PROJECT_NAME} X-FS)
