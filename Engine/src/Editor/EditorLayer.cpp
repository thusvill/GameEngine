//
// Created by bios on 10/6/23.
//

#include "EditorLayer.h"
#include "../ImGuiLayer/ImgGuiSRC.h"
#include "../VectorVertex/Application.h"
#include "../VectorVertex/Renderer.h"
namespace VectorVertex {
    bool StyleEditorOpened = false;
    EditorLayer::EditorLayer(): Layer("EditorLayer") {}

    Scope<Model> model;
    Ref<Shader> model_shader;

    void EditorLayer::OnAttach() {
        m_EditorCamera = Camera::Create(m_CameraProps);
        m_EditorCamera->GetProperties().Position = glm::vec3(0.0f);
        m_FrameBuffer = FrameBuffer::Create(800, 700);
        model_shader = Shader::Create("default", "/home/bios/CLionProjects/GameEngine/GameEngine/Engine/res/Shaders/default.vert", "/home/bios/CLionProjects/GameEngine/GameEngine/Engine/res/Shaders/default.frag", "/home/bios/CLionProjects/GameEngine/GameEngine/Engine/res/Shaders/default.geom");
        m_ShaderLibrary.Add(model_shader);
        model_shader->SetFloat4("lightColor", glm::vec4(1.0f));
        model_shader->SetFloat3("lightPos", glm::vec3(1.0f));
        model = Model::Create("/home/bios/CLionProjects/Game/Models/statue/scene.gltf");
        model->SetTransform(model_shader,glm::vec3(0.1f), glm::vec3(0.1f), glm::vec3(1.0f));

    }

    void EditorLayer::BindFrameBuffer() {
        m_FrameBuffer->Bind();
    }

    void EditorLayer::UnbindFrameBuffer() {
        m_FrameBuffer->Unbind();
    }

    void EditorLayer::OnDetach() {

    }

    void EditorLayer::OnUpdate(){
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        m_EditorCamera->Inputs(window);
        m_EditorCamera->updateMatrix();
    }

    void EditorLayer::OnRender() {
        model->Draw(model_shader, *m_EditorCamera);
       //VV_CORE_WARN("Model Position x:{0} y:{1} z:{2}",model->GetPosition().x, model->GetPosition().y, model->GetPosition().z);
    }

    void EditorLayer::OnImGuiRender() {
        //FrameBuffer
        {
            ImGui::Begin("Viewport");

            GLuint fboTextureID = m_FrameBuffer->GetRenderTexture();
            ImVec2 panelSize = ImGui::GetContentRegionAvail();
            if (panelSize.x != m_EditorCamera->GetProperties().width || panelSize.y != m_EditorCamera->GetProperties().height) {
                m_EditorCamera->Resize(panelSize.x, panelSize.y);
                glViewport(0, 0, panelSize.x, panelSize.y);
                m_FrameBuffer->Resize(panelSize.x, panelSize.y);
            }
            ImGui::Image(reinterpret_cast<void *>(static_cast<uintptr_t>(fboTextureID)),
                         ImVec2(panelSize.x, panelSize.y), ImVec2(0, 1), ImVec2(1, 0));

            ImGui::End();
        }
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
    }
} // VectorVertex