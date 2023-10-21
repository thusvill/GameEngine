//
// Created by bios on 9/6/23.
//

#include "Application.h"
namespace VectorVertex{
    Application* Application::s_Instance = nullptr;
    Application::Application(const ApplicationSpecs &specs): m_AppSpecs(specs) {

        if(!s_Instance) {
            s_Instance = this;
        }else{
            VV_CORE_ERROR("Application already exists!");
            return;
        }
        m_Window = Window::Create(WindowProps(m_AppSpecs.Name, (uint32_t)m_AppSpecs.width, (uint32_t)m_AppSpecs.height));
        m_ImGuiLayer = new ImguiLayer();
        PushOverlay(m_ImGuiLayer);

        m_EditorLayer = new EditorLayer();
        PushOverlay(m_EditorLayer);
        //m_EditorLayer->m_ShaderLibrary.Load("/home/bios/CLionProjects/GameEngine/GameEngine/Engine/res/Shaders/default_shader.glsl");

    }

    void Application::PushLayer(VectorVertex::Layer *layer) {
        m_LayerStack.PushLayer(layer);
        //layer->OnAttach();
    }

    void Application::PushOverlay(VectorVertex::Layer *layer) {
        m_LayerStack.PushOverlay(layer);
        VV_CORE_INFO("PushingOverlay");
       // layer->OnAttach();
    }

    void Application::OnStart() {
        VV_CORE_WARN("Started!");
        RenderAPI::SetAPI(RenderAPI::API::OpenGL);

    }
    void Application::Run() {

        while (true){


            if(!m_ImGuiLayer){
                VV_CORE_ERROR("ImGui Layer not found!");
                return;
            }
            {
                glClearColor(0.26f, 0.26f, 0.26f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                m_EditorLayer->BindFrameBuffer();
                glClearColor(0.26f, 0.26f, 0.26f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                m_Window->OnRender();
                m_EditorLayer->UnbindFrameBuffer();

                m_ImGuiLayer->Begin();
                //ShowDockSpace
                if(DockSpaceEnabled) {
                    m_ImGuiLayer->ShowDockSpace(nullptr);
                }
                if(ExternalViewpoertsEnabled){
                    m_ImGuiLayer->UpdateViewports();
                }
                {
                    for (Layer *layer: m_LayerStack)
                        layer->OnImGuiRender();
                }
                {
                    for (Layer *layer: m_LayerStack) {
                        layer->OnUpdate();
                    }
                }
                m_ImGuiLayer->End();
                m_Window->OnUpdate();

            }
        }
        Stop();
    }

    void Window::OnUpdate() {
    }

    void Application::Stop() {

        delete m_ImGuiLayer;
        delete m_EditorLayer;
    }
    void Window::OnStart() {

    }
    void Window::OnRender() {
        for (Layer *layer: Application::Get().m_LayerStack) {
            if(!layer){
                VV_CORE_ERROR("Layer {} is Null or empty!", layer->GetName());
            }
            layer->OnRender();
        }
        /*glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);   // Red
        glVertex2f(0.0f, 0.5f);         // Top
        glColor3f(0.0f, 1.0f, 0.0f);   // Green
        glVertex2f(-0.5f, -0.5f);       // Bottom left
        glColor3f(0.0f, 0.0f, 1.0f);   // Blue
        glVertex2f(0.5f, -0.5f);        // Bottom right
        glEnd();
*/
    }

}