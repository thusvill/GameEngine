cmake_minimum_required(VERSION 3.25)
project(VectorVertex)

set(CMAKE_CXX_STANDARD 23)
file(GLOB_RECURSE SRC_FILES "Engine/**.cpp" "Engine/**.h")
file(GLOB IMGUI_SRC "Engine/vendor/imgui/**.cpp" " Engine/vendor/imgui/**.h")
add_executable(VectorVertex Projects/Sandbox/Sandbox.cpp ${SRC_FILES} Engine/src/Renderer/Camera.cpp Engine/src/Renderer/Camera.h Engine/src/Plattform/OpenGL/OpenGLContext.cpp Engine/src/Plattform/OpenGL/OpenGLContext.h Engine/src/Renderer/GraphicsContext.cpp Engine/src/Renderer/GraphicsContext.h Engine/src/Core/Window.cpp Engine/src/Core/Window.h Engine/src/Core/LayerStack.cpp Engine/src/Core/LayerStack.h Engine/src/Core/PlattformDetection.h Engine/src/Plattform/Linux/LinuxWindow.cpp Engine/src/Plattform/Linux/LinuxWindow.h Engine/src/Core/ErrorDetection.h )

add_library(glad STATIC Engine/vendor/glad/src/glad.c)
add_library(imgui ${IMGUI_SRC})
target_include_directories(glad PUBLIC Engine/vendor/glad/include)
target_include_directories(imgui PUBLIC "Engine/vendor/imgui")

find_package(glm REQUIRED)

target_link_libraries(VectorVertex PRIVATE glad glfw fmt imgui)

target_compile_options(VectorVertex PRIVATE -g)