//
// Created by bios on 9/7/23.
//

#ifndef GAMEENGINE_OPENGLVBO_H
#define GAMEENGINE_OPENGLVBO_H
#include "iostream"
#include "vector"
#include "../../../vendor/glad/include/glad/glad.h"
#include "glm/glm.hpp"

namespace VectorVertex {
    struct GLVertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        glm::vec2 texUV;
    };

    class OpenGLVBO {
    public:
        GLuint ID;

        OpenGLVBO(std::vector<GLVertex> &vertices);

        void Bind();

        void Unbind();

        void Delete();
    };

}
#endif //GAMEENGINE_OPENGLVBO_H
