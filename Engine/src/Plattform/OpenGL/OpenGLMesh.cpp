//
// Created by bios on 9/12/23.
//

#include "OpenGLMesh.h"
#include "OpenGLCamera.h"
namespace VectorVertex{

    OpenGLMesh::OpenGLMesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures) {
        OpenGLMesh::vertices = vertices;
        OpenGLMesh::indices = indices;
        for (int i = 0; i < OpenGLMesh::textures.capacity(); ++i) {
            for (int j = 0; j < textures.capacity(); ++j) {
                OpenGLMesh::textures[i] = static_cast<OpenGLTexture*>(textures[j].GetTexture());
            }
        }

        vao.Bind();
        // Generates Vertex Buffer Object and links it to vertices
        OpenGLVBO VBO(vertices);
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

    }

    void OpenGLMesh::Draw(Ref<Shader> _shader, Camera &i_camera, glm::mat4 matrix, glm::vec3 translation, glm::quat rotation,
                    glm::vec3 scale) {
        OpenGLCamera* camera = static_cast<OpenGLCamera*>(i_camera.GetCamera());
        GLShader* shader = static_cast<GLShader*>(_shader->GetShader());
        shader->Activate();
        vao.Bind();

        unsigned int numDiffuse = 0;
        unsigned int numSpecular = 0;

        for (unsigned int i = 0; i < textures.size(); ++i) {
            std::string num;
            std::string type = textures[i]->GetData().type;
            if(type == "diffuse"){
                num = std::to_string(numDiffuse++);
            } else if (type == "specular"){
                num = std::to_string(numSpecular++);
            }
            textures[i]->texUni(shader, (type +num).c_str(), i);
            textures[i]->Bind();

        }
        // Take care of the camera Matrix
        glUniform3f(glGetUniformLocation(shader->ID, "camPos"), camera->m_CameraProperties.Position.x, camera->m_CameraProperties.Position.y, camera->m_CameraProperties.Position.z);
        camera->Matrix(shader, "camMatrix");

        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 rot = glm::mat4(1.0f);
        glm::mat4 sca = glm::mat4(1.0f);

        glUniformMatrix4fv(glGetUniformLocation(shader->ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
        glUniformMatrix4fv(glGetUniformLocation(shader->ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
        glUniformMatrix4fv(glGetUniformLocation(shader->ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
        glUniformMatrix4fv(glGetUniformLocation(shader->ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

        // Draw the actual mesh
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    }
}