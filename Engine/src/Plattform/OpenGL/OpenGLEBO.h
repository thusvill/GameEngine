//
// Created by bios on 9/7/23.
//

#ifndef GAMEENGINE_OpenGLEBO_H
#define GAMEENGINE_OpenGLEBO_H
#include "iostream"
#include "vector"
#include "../../../vendor/glad/include/glad/glad.h"

namespace VectorVertex{
    class OpenGLEBO {
    public:
        GLuint ID;
        OpenGLEBO(std::vector <GLuint>& indices);

        void Bind();
        void Unbind();
        void Delete();
    };
}

#endif //GAMEENGINE_OpenGLEBO_H
