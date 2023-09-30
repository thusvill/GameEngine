cmake_minimum_required(VERSION 3.25)
project(VectorVertex)

set(CMAKE_CXX_STANDARD 23)
file(GLOB_RECURSE SRC_FILES "Engine/**.cpp" "Engine/**.h")
add_executable(VectorVertex Projects/Sandbox/Sandbox.cpp ${SRC_FILES} Engine/src/Renderer/Camera.cpp Engine/src/Renderer/Camera.h)

add_library(glad STATIC Engine/vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC Engine/vendor/glad/include)

find_package(glm REQUIRED)

target_link_libraries(VectorVertex PRIVATE glad glfw fmt)