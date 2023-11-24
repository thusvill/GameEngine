//
// Created by bios on 9/12/23.
//

#include "OpenGLMesh.h"
#include "OpenGLCamera.h"
namespace VectorVertex{
OpenGLMesh::OpenGLMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Ref<Texture>>& i_textures) :vertices(vertices), indices(indices), textures(i_textures){
  vao.Bind();

  VV_CORE_ASSERT(vertices.size() > 0, "Vertices are 0!");
  VV_CORE_ASSERT(indices.size() > 0, "Indices are 0!");
  VV_CORE_ASSERT(textures.size() > 0, "Textures are 0!");

  OpenGLVBO vbo(vertices);
  OpenGLEBO ebo(indices);

  vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
  vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
  vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
  vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

  vao.Unbind();
  vbo.Unbind();
  ebo.Unbind();

}

void OpenGLMesh::Draw(Ref<VectorVertex::Shader> shader, Ref<VectorVertex::Camera> i_camera, glm::mat4 matrix, glm::vec3 translation, glm::quat rotation, glm::vec3 scale) {
  shader->Activate();
  unsigned int numDiffuse = 0;
  unsigned int numSpecular = 0;

  for (unsigned int i = 0; i < textures.size(); ++i) {
    std::string num;
    std::string type(textures[i]->GetData().type);
    if (type == "diffuse") {
      num = std::to_string(numDiffuse++);
    } else if (type == "specular") {
      num = std::to_string(numSpecular++);
    }
    textures[i]->texUni(shader, (type + num), i);
    textures[i]->Bind();
  }
  vao.Bind();
    GLCall(shader->SetFloat3("camPos", i_camera->GetProperties().Position));
    i_camera->Matrix(shader, "camMatrix");

    /*glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    shader->SetMat4("translation", trans);
    shader->SetMat4("rotation", rot);
    shader->SetMat4("scale", sca);
    shader->SetMat4("model", matrix);
*/
    // Draw the actual mesh
    GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
    //vao.Unbind();
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      std::cerr << "OpenGL error: " << error << std::endl;
    }

}
}