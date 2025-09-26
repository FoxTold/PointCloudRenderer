cmake_minimum_required(VERSION 3.20)

project(Renderer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RC_STANDARD_REQUIRED ON)
set(GLFW_USE_WAYLAND ON)

find_package(OpenGL REQUIRED)

add_subdirectory(deps)

add_executable(Renderer
    src/main.cpp
    src/Renderer.cpp
    src/Triangle.cpp
    ${CMAKE_SOURCE_DIR}/deps/glad/src/glad.c
)

target_include_directories(Renderer PRIVATE
    include
    ${CMAKE_SOURCE_DIR}/deps/glad/include
)

target_link_libraries(Renderer PRIVATE
    OpenGL::GL
    glfw
    glm
)
