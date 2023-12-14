//
// Created by bios on 9/7/23.
//

#include "OpenGLVAO.h"

namespace VectorVertex{
    OpenGLVAO::OpenGLVAO() {
        glGenVertexArrays(1, &ID);
        Bind();
        VV_CORE_INFO("VAO Created!");
    }

    void OpenGLVAO::LinkAttrib(OpenGLVBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
        if(ID <= 0){
          glGenVertexArrays(1, &ID);
          VV_CORE_INFO("VAO not exist!, Automatically created one");
        }
        //VBO.Bind();
        GLCall(glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset));
        GLCall(glEnableVertexAttribArray(layout));
        //VBO.Unbind();
    }

    void OpenGLVAO::Bind()  {
        glBindVertexArray(ID);
    }

    void OpenGLVAO::Unbind() {
        glBindVertexArray(0);
    }

    void OpenGLVAO::Delete() {
        glDeleteVertexArrays(1, &ID);
    }
}