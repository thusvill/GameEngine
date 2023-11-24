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

        virtual void Draw(Ref<Shader> shader,Ref<Camera> camera)=0;
        virtual void Position(Ref<Shader> shader,glm::vec3 newPosition)=0;
        virtual void Rotation(Ref<Shader> shader,glm::vec3 rotation)=0;
        virtual void Scale(Ref<Shader> shader,glm::vec3 newScale)=0;
        virtual void SetTransform(Ref<Shader> shader,glm::vec3 position,glm::vec3 rotation,glm::vec3 scale)=0;
        virtual glm::vec3 GetPosition() =   0;
        virtual glm::vec3 GetScale()  =0;
        virtual glm::vec3 GetRotation() =0;

        static Ref<Model>Create(const char* file);


    };

} // VectorVertex

#endif //GAMEENGINE_MODEL_H
