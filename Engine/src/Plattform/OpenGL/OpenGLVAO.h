//
// Created by bios on 9/7/23.
//

#ifndef GAMEENGINE_OPENGLVAO_H
#define GAMEENGINE_OPENGLVAO_H
#include "../../../vendor/glad/include/glad/glad.h"
#include "OpenGLVBO.h"

namespace VectorVertex {
    class OpenGLVAO {
    public:
        GLuint ID;

        OpenGLVAO();
        ~OpenGLVAO(){
          Delete();
        }

        void LinkAttrib(OpenGLVBO& VBO,
        GLuint layout, GLuint
        numComponents,
        GLenum type, GLsizeiptr
        stride,
        void *offset
        );

        void Bind();

        void Unbind();

        void Delete();
    };

}
#endif //GAMEENGINE_OPENGLVAO_H
