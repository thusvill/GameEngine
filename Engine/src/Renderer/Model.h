//
// Created by bios on 10/9/23.
//

#ifndef GAMEENGINE_MODEL_H
#define GAMEENGINE_MODEL_H
#include "Shader.h"
#include "Camera.h"
#include "glm/glm.hpp"
namespace VectorVertex {

    class Model {
    public:
        virtual ~Model() = default;

        virtual void Draw(Camera& camera)=0;
        virtual void Position(glm::vec3 newPosition)=0;
        virtual void Rotation(glm::vec3 rotation)=0;
        virtual void Scale(glm::vec3 newScale)=0;
        virtual void SetTransform(glm::vec3 position,glm::vec3 rotation,glm::vec3 scale)=0;
        virtual void UpdateShader(Ref<Shader> shader)=0;
        virtual glm::vec3 GetPosition() =   0;
        virtual Ref<Shader> GetShader()=0;

        static Scope<Model>Create(const char* file, Ref<Shader> shader);


    };

} // VectorVertex

#endif //GAMEENGINE_MODEL_H
