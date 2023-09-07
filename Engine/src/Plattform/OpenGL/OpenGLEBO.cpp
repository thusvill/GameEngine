//
// Created by bios on 9/7/23.
//

#include "OpenGLEBO.h"

namespace VectorVertex {
    OpenGLEBO::OpenGLEBO(std::vector <GLuint> &indices) {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }

    void OpenGLEBO::Bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    void OpenGLEBO::Unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void OpenGLEBO::Delete() {
        glDeleteBuffers(1, &ID);
    }
}