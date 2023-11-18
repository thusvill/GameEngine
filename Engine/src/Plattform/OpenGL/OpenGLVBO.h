//
// Created by bios on 9/7/23.
//

#ifndef GAMEENGINE_OPENGLVBO_H
#define GAMEENGINE_OPENGLVBO_H
#include "iostream"
#include "vector"
#include "../../../vendor/glad/include/glad/glad.h"
#include "glm/glm.hpp"
#include "../../Renderer/Mesh.h"

namespace VectorVertex {


    class OpenGLVBO {
    public:
        GLuint ID;

        OpenGLVBO(std::vector<Vertex> &vertices);
        ~OpenGLVBO(){
          Delete();
        }

        void Bind();

        void Unbind();

        void Delete();

        bool Empty(){
            return empty;
        }
    private:
        bool empty = true;
    };

}
#endif //GAMEENGINE_OPENGLVBO_H
