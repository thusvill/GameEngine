//
// Created by bios on 9/12/23.
//

#include "OpenGLMesh.h"
namespace VectorVertex{

    OpenGLMesh::OpenGLMesh(std::vector <GLVertex>& vertices, std::vector <GLuint>& indices, std::vector <OpenGLTexture>& textures) {
        OpenGLMesh::vertices = vertices;
        OpenGLMesh::indices = indices;
        OpenGLMesh::textures = textures;

        vao.Bind();
        // Generates Vertex Buffer Object and links it to vertices
        OpenGLVBO VBO(vertices);
        // Generates Element Buffer Object and links it to indices
        OpenGLEBO EBO(indices);
        // Links VBO attributes such as coordinates and colors to vao
        vao.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(GLVertex), (void*)0);
        vao.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(GLVertex), (void*)(3 * sizeof(float)));
        vao.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(GLVertex), (void*)(6 * sizeof(float)));
        vao.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(GLVertex), (void*)(9 * sizeof(float)));
        // Unbind all to prevent accidentally modifying them
        vao.Unbind();
        VBO.Unbind();
        EBO.Unbind();

    }



    void OpenGLMesh::Draw(GLShader &shader, OpenGLCamera &camera, glm::mat4 matrix, glm::vec3 translation, glm::quat rotation,
                    glm::vec3 scale) {
        shader.Activate();
        vao.Bind();

        unsigned int numDiffuse = 0;
        unsigned int numSpecular = 0;

        for (unsigned int i = 0; i < textures.size(); ++i) {
            std::string num;
            std::string type = textures[i].type;
            if(type == "diffuse"){
                num = std::to_string(numDiffuse++);
            } else if (type == "specular"){
                num = std::to_string(numSpecular++);
            }
            textures[i].texUni(shader, (type +num).c_str(), i);
            textures[i].Bind();

        }
        // Take care of the camera Matrix
        glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.m_CameraProperties.Position.x, camera.m_CameraProperties.Position.y, camera.m_CameraProperties.Position.z);
        camera.Matrix(shader, "camMatrix");

        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 rot = glm::mat4(1.0f);
        glm::mat4 sca = glm::mat4(1.0f);

        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

        // Draw the actual mesh
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    }
}