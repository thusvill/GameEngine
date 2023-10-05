//
// Created by bios on 10/5/23.
//
#pragma once
#ifndef GAMEENGINE_ERRORDETECTION_H
#define GAMEENGINE_ERRORDETECTION_H
#include "../../vendor/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace VectorVertex {
#define GLClearError() while (glGetError() != GL_NO_ERROR)

    inline bool GLLogCall(const char *function, const char *file, int line) {
        while (GLenum error = glGetError()) {
            std::cerr << "OpenGL error: " << error << " in " << function
                      << " at " << file << ":" << line << std::endl;

            return false;
        }
        return true;
    }

#define ASSERT(x) if (!(x)) __builtin_trap();

#define GLCall(x) \
    GLClearError(); \
    x; \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
}
#endif //GAMEENGINE_ERRORDETECTION_H
