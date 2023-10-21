//
// Created by bios on 10/9/23.
//

#ifndef GAMEENGINE_OPENGLMODEL_H
#define GAMEENGINE_OPENGLMODEL_H

#include "../../../vendor/json/json.h"
#include "../../Renderer/Mesh.h"
#include "../../VectorVertex/Core.h"
#include "../../Renderer/Model.h"

namespace VectorVertex {
    using json = nlohmann::json;


    class OpenGLModel : public Model {
    public:
        OpenGLModel(const char* file);
        virtual ~OpenGLModel() {
        }

        virtual void Draw(Ref<Shader> shader,Camera& camera) override;
        virtual void Position(Ref<Shader> shader,glm::vec3 newPosition) override;
        virtual void Rotation(Ref<Shader> shader,glm::vec3 rotation) override;
        virtual void Scale(Ref<Shader> shader,glm::vec3 newScale) override;
        virtual void SetTransform(Ref<Shader> shader,glm::vec3 position,glm::vec3 rotation,glm::vec3 scale) override;
        virtual glm::vec3 GetPosition() override;

        explicit operator bool() const {
            // Define the condition under which the Model is considered "true"
            return !meshes.empty(); // For example, consider it "true" if meshes are loaded
        }
    private:
        glm::vec3 m_Position;

    private:
        const char* file;
        std::vector<unsigned char> data;
        json JSON;

        std::vector<Ref<Mesh>> meshes;
        std::vector<glm::vec3> translationMeshes;
        std::vector<glm::quat> rotationMeshes;
        std::vector<glm::vec3> scalesMeshes;
        std::vector<glm::mat4> matricesMeshes;

        std::vector<std::string> loadedTexName;
        std::vector<Ref<Texture>> loadedTex;

        void loadMesh(unsigned int indMesh);
        void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

        std::vector<unsigned char> getData();
        std::vector<float> getFloats(json accessor);
        std::vector<GLuint> getIndices(json accessor);
        std::vector<Ref<Texture>> getTexture();

        std::vector<Vertex> assembleVertices
                (
                        std::vector<glm::vec3> positions,
                        std::vector<glm::vec3> normals,
                        std::vector<glm::vec2> texUVs
                );

        std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
        std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
        std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
    };


} // VectorVertex

#endif //GAMEENGINE_OPENGLMODEL_H
