//
// Created by bios on 9/12/23.
//

#ifndef GAMEENGINE_OPENGLMESH_H
#define GAMEENGINE_OPENGLMESH_H

#include <string>

#include "OpenGLVAO.h"
#include "OpenGLEBO.h"
#include "OpenGLCamera.h"
#include "OpenGLTexture.h"

namespace VectorVertex {
    class OpenGLMesh {
    public:
        std::vector <GLVertex> vertices;
        std::vector <GLuint> indices;
        std::vector <OpenGLTexture> textures;

        OpenGLVAO vao;

        OpenGLMesh(std::vector <GLVertex>& vertices, std::vector <GLuint>& indices, std::vector <OpenGLTexture>& textures);

        void Draw(
                GLShader& shader,
                OpenGLCamera& camera,
                glm::mat4 matrix = glm::mat4(1.0f),
                glm::vec3 translation = glm::vec3(0.0f),
                glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
                glm::vec3 scale = glm::vec3(1.0f)
        );


    };
}

#endif //GAMEENGINE_OPENGLMESH_H
