//
// Created by bios on 9/12/23.
//

#ifndef GAMEENGINE_OPENGLMESH_H
#define GAMEENGINE_OPENGLMESH_H

#include <string>

#include "OpenGLVAO.h"
#include "OpenGLEBO.h"
#include "OpenGLTexture.h"
#include "GLShader.h"
#include "../../Renderer/Mesh.h"
#include "../../Core/Log.h"

namespace VectorVertex {
    class OpenGLMesh : public Mesh {
    public:
        std::vector <Vertex> vertices;
        std::vector <GLuint> indices;
        std::vector <Ref<Texture>> textures;

        OpenGLVAO vao;

        OpenGLMesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Ref<Texture>> &i_textures);
        virtual ~OpenGLMesh(){
            VV_CORE_WARN("Deleting Mesh");
        }

        virtual void Draw(Ref<Shader> shader, Camera &i_camera, glm::mat4 matrix, glm::vec3 translation= glm::vec3 (0.0f), glm::quat rotation = glm::quat (1.0f, 0.0f, 0.0f, 0.0f),
                          glm::vec3 scale = glm::vec3(1.0f)) override;


    };
}

#endif //GAMEENGINE_OPENGLMESH_H
