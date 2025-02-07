cmake_minimum_required(VERSION 3.28)
project(OpenGL)
add_executable(OpenGL main.cpp vendor/glad./src/glad.c)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SDL_STATIC True)
set(SDL_EXAMPLES True)

target_include_directories(OpenGL PRIVATE vendor/glad./include PRIVATE vendor/glm)
target_link_libraries(OpenGL PRIVATE SDL3::SDL3-static)
add_subdirectory(vendor/SDL)


