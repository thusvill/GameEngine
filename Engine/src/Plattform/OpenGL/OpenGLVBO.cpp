//
// Created by bios on 9/7/23.
//

#include "OpenGLVBO.h"

namespace VectorVertex{
    OpenGLVBO::OpenGLVBO(std::vector <Vertex>& vertices) {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        VV_CORE_ASSERT(!vertices.empty(),"Vertices is NULL in OpenGLVBO");
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
        empty= false;
    }

    void OpenGLVBO::Bind() {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    void OpenGLVBO::Unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVBO::Delete() {
        glDeleteBuffers(1, &ID);
    }
}