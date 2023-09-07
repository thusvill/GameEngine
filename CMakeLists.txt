cmake_minimum_required(VERSION 3.25)
project(GameEngine)

set(CMAKE_CXX_STANDARD 23)
file(GLOB_RECURSE SRC_FILES "Engine/**.cpp" "Engine/**.h")
add_executable(GameEngine ${SRC_FILES} Projects/Sandbox/Sandbox.cpp)

add_library(glad STATIC Engine/vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC Engine/vendor/glad/include)

find_package(glm REQUIRED)

target_link_libraries(GameEngine PRIVATE glad glfw)