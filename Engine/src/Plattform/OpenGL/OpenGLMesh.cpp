//
// Created by bios on 9/12/23.
//

#include "OpenGLMesh.h"
#include "OpenGLCamera.h"
namespace VectorVertex{

    OpenGLMesh::OpenGLMesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Ref<Texture>> &i_textures) {

        OpenGLMesh::vertices = vertices;
        OpenGLMesh::indices = indices;
        VV_CORE_ASSERT(!vertices.empty(), "Vertices NULL in GLMesh");
        VV_CORE_ASSERT(!indices.empty(), "Indices NULL in GLMesh");
        //for (auto& i_texture : i_textures) {
        //    textures.emplace_back(i_texture);
        //    }
        textures = i_textures;
        VV_CORE_ASSERT(!i_textures.empty(), "Textures is NULL in GLMesh");

        for (int i = 0; i < textures.size(); ++i) {

            VV_CORE_INFO("Texture added: {}", textures[i]->GetData().image);
        }

        vao.Bind();
        // Generates Vertex Buffer Object and links it to vertices
        OpenGLVBO VBO(vertices);
        VV_CORE_ASSERT(!VBO.Empty(), "GLVBO NULL in GLMesh");
        // Generates Element Buffer Object and links it to indices
        OpenGLEBO EBO(indices);
        // Links VBO attributes such as coordinates and colors to vao
        vao.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
        vao.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
        vao.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
        vao.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
        // Unbind all to prevent accidentally modifying them
        vao.Unbind();
        VBO.Unbind();
        EBO.Unbind();
        VV_CORE_INFO("Mesh created with {0} vertices, {1} indices, {2} textures", vertices.size(), indices.size(), textures.size());

    }

    void OpenGLMesh::Draw(Ref<Shader> shader, Ref<Camera> i_camera, glm::mat4 matrix, glm::vec3 translation, glm::quat rotation,
                    glm::vec3 scale) {
        if(!i_camera){
            VV_CORE_ERROR("Draw Mesh camera NULL!");
        }
        if(!shader){
            VV_CORE_ERROR("Draw Mesh shader NULL!");
        }

        shader->Activate();
        vao.Bind();

        unsigned int numDiffuse = 0;
        unsigned int numSpecular = 0;
        if(textures.size() <=0 ){
            VV_CORE_WARN("No Textures found in Draw FUNC!");
        } else
        {
            for (unsigned int i = 0; i < textures.size(); ++i) {
                std::string num;
                std::string type = textures[i]->GetData().type;
                if (type == "diffuse") {
                    num = std::to_string(numDiffuse++);
                } else if (type == "specular") {
                    num = std::to_string(numSpecular++);
                }
                textures[i]->texUni(shader, (type + num).c_str(), i);
                textures[i]->Bind();
                //VV_CORE_INFO("Bound {0} shader with uniform: {1}{2} in unit {3}",type,type,num, i);

            }
        }
        // Take care of the camera Matrix
        glUniform3f(glGetUniformLocation(shader->GetID(), "camPos"), i_camera->GetProperties().Position.x, i_camera->GetProperties().Position.y, i_camera->GetProperties().Position.z);
        i_camera->Matrix(shader, "camMatrix");

        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 rot = glm::mat4(1.0f);
        glm::mat4 sca = glm::mat4(1.0f);

        glUniformMatrix4fv(glGetUniformLocation(shader->GetID(), "translation"), 1, GL_FALSE, glm::value_ptr(trans));
        glUniformMatrix4fv(glGetUniformLocation(shader->GetID(), "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
        glUniformMatrix4fv(glGetUniformLocation(shader->GetID(), "scale"), 1, GL_FALSE, glm::value_ptr(sca));
        glUniformMatrix4fv(glGetUniformLocation(shader->GetID(), "model"), 1, GL_FALSE, glm::value_ptr(matrix));

        // Draw the actual mesh
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    }
}