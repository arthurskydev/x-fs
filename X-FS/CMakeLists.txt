cmake_minimum_required(VERSION 3.23)

add_subdirectory(src/X-FS)


target_include_directories(${PROJECT_NAME} PRIVATE src/X-FS)
target_include_directories(${PROJECT_NAME} PUBLIC src)

