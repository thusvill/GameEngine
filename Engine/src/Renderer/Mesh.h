//
// Created by bios on 10/9/23.
//

#ifndef GAMEENGINE_MESH_H
#define GAMEENGINE_MESH_H
#include "Texture.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
namespace VectorVertex {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        glm::vec2 texUV;
    };

    class Mesh {
    public:
        virtual ~Mesh()=default;

        virtual void Draw(
                Ref<Shader> shader,
                Camera& i_camera,
                glm::mat4 matrix = glm::mat4(1.0f),
                glm::vec3 translation = glm::vec3(0.0f),
                glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
                glm::vec3 scale = glm::vec3(1.0f)
                )=0;

        static Scope<Mesh> Create(std::vector <Vertex>& vertices, std::vector <unsigned int>& indices, std::vector <Scope<Texture>> &textures);
    };

} // VectorVertex

#endif //GAMEENGINE_MESH_H
