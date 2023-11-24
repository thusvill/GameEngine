//
// Created by bios on 10/6/23.
//

#include "EditorLayer.h"
#include "../ImGuiLayer/ImgGuiSRC.h"
#include "../VectorVertex/Application.h"
#include "../VectorVertex/Renderer.h"

#include "glm/gtc/matrix_transform.hpp"
#include "../Plattform/OpenGL/OpenGLMesh.h"
namespace VectorVertex {
    bool StyleEditorOpened = false;
    EditorLayer::EditorLayer(): Layer("EditorLayer") {

    }

    Ref<Model> model;
    Ref<Shader> model_shader;


    void EditorLayer::OnAttach() {
        m_EditorCamera = Camera::Create(m_CameraProps);
      m_EditorCamera->GetProperties().Position = glm::vec3(-1.0f);
      //m_FrameBuffer = FrameBuffer::Create(800,700);

      //model_shader = Shader::Create("default", "/home/bios/CLionProjects/GameEngine/GameEngine/Engine/res/Shaders/default.vert", "/home/bios/CLionProjects/GameEngine/GameEngine/Engine/res/Shaders/default.frag", "/home/bios/CLionProjects/GameEngine/GameEngine/Engine/res/Shaders/default.geom");
      //m_ShaderLibrary.Add(model_shader);
      model_shader = m_ShaderLibrary.Load("/home/bios/CLionProjects/GameEngine/GameEngine/Engine/res/Shaders/default.glsl");
      model_shader->Activate();

      model = Model::Create("/home/bios/CLionProjects/Game/Models/bunny/scene.gltf");

      model->Position(model_shader, glm::vec3(1.0f));
      model->Rotation(model_shader, glm::vec3(0.1f));
      model->Scale(model_shader, glm::vec3(1.0f, 1.0f, 1.0f));



    }

    void EditorLayer::BindFrameBuffer() {
        //m_FrameBuffer->Bind();
    }

    void EditorLayer::UnbindFrameBuffer() {
        //m_FrameBuffer->Unbind();
    }

    void EditorLayer::OnDetach() {

    }

    void EditorLayer::OnUpdate(){
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        m_EditorCamera->Inputs(window);
    }
    void ExampleTriangle(){
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); // Red
        glVertex3f(0.0f, 0.5f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f); // Green
        glVertex3f(-0.5f, -0.5f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f); // Blue
        glVertex3f(0.5f, -0.5f, 0.0f);
        glEnd();
    }

    void EditorLayer::OnRender() {
      //model->Draw(model_shader, m_EditorCamera);
      m_EditorCamera->updateMatrix();
      ExampleTriangle();
      GLenum err;
      if ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << err << std::endl;
      }
    }
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scal;

    void EditorLayer::OnImGuiRender() {
        //FrameBuffer
        {
            ImGui::Begin("Viewport");

            //GLuint fboTextureID = m_FrameBuffer->GetRenderTexture();
            ImVec2 panelSize = ImGui::GetContentRegionAvail();
            if (panelSize.x != m_EditorCamera->GetProperties().width || panelSize.y != m_EditorCamera->GetProperties().height) {
                //m_EditorCamera->Resize(panelSize.x, panelSize.y);
                glViewport(0, 0, panelSize.x, panelSize.y);
                //m_FrameBuffer->Resize(panelSize.x, panelSize.y);
            }
            //ImGui::Image(reinterpret_cast<void *>(static_cast<uintptr_t>(fboTextureID)),
             //            ImVec2(panelSize.x, panelSize.y), ImVec2(0, 1), ImVec2(1, 0));

            ImGui::End();
        }
        //Camera
        {
            ImGui::Begin("Camera");
            ImGui::Text("Position x:%f  y:%f  z:%f", m_EditorCamera->GetProperties().Position.x, m_EditorCamera->GetProperties().Position.y, m_EditorCamera->GetProperties().Position.z);
            ImGui::Text("Rotation x:%f  y:%f  z:%f", m_EditorCamera->GetProperties().Orientation.x, m_EditorCamera->GetProperties().Orientation.y, m_EditorCamera->GetProperties().Orientation.z);
            ImGui::End();
        }
        //Model
        {
            ImGui::Begin("Model");
            ImGui::Text("Position x:%f  y:%f  z:%f", model->GetPosition().x,model->GetPosition().y,model->GetPosition().z);
            ImGui::DragFloat3("Pos", glm::value_ptr(pos), 0.5f);
            ImGui::Text("Rotation x:%f  y:%f  z:%f", model->GetRotation().x,model->GetRotation().y,model->GetRotation().z);
            ImGui::DragFloat3("Rot", glm::value_ptr(rot), 0.2f);
            ImGui::Text("Scale x:%f  y:%f  z:%f", model->GetScale().x,model->GetScale().y,model->GetScale().z);
            ImGui::DragFloat3("Scal", glm::value_ptr(scal), 0.2f);
          model->Position(model_shader, pos);
          model->Rotation(model_shader, rot);
          model->Scale(model_shader,scal);
            ImGui::End();
        }

        //Settings
        {
            ImGui::Begin("Settings");
            ImGui::Text("VectorVertex Engine V1.0");
            ImGui::SeparatorText("OpenGL Informations");
            ImGui::Text("  Vendor: %s", glGetString(GL_VENDOR));
            ImGui::Text("  Renderer: %s", glGetString(GL_RENDERER));
            ImGui::Text("  Version: %s", glGetString(GL_VERSION));
            ImGui::SeparatorText("Styles");
            ImGui::Checkbox("Dockspace", &Application::Get().DockSpaceEnabled);
            ImGui::Checkbox("Editor Layout", &StyleEditorOpened);
            if ( StyleEditorOpened)
            {
                ImGui::Begin("Styles Editor");
                ImGui::ShowStyleEditor();
                ImGui::End();
            }
            ImGui::End();
        }

        //In Development
        /*
        {
            //Scene Hierarchy
            {
                ImGui::Begin("Scene");
                ImGui::End();
            }
            //Console
            {
                ImGui::Begin("Console");
                ImGui::End();
            }
            //Browser
            {
                ImGui::Begin("Browser");
                ImGui::End();
            }
        }
        */
    }
} // VectorVertex