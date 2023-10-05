//
// Created by bios on 9/6/23.
//

#include "Application.h"

namespace VectorVertex{
    Application* Application::s_Instance = nullptr;
    Application::Application(const ApplicationSpecs &specs): m_AppSpecs(specs) {
        m_Window = Window::Create(WindowProps(m_AppSpecs.Name));
        if(!s_Instance) {
            s_Instance = this;
        }
        m_ImGuiLayer = new ImguiLayer();
        PushOverlay(m_ImGuiLayer);

    }
    Application::~Application() {
    }

    void Application::PushLayer(VectorVertex::Layer *layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(VectorVertex::Layer *layer) {
        m_LayerStack.PushOverlay(layer);
#if defined(VV_DEBUG)
        VV_CORE_INFO("PushingOverlay");
#endif
        layer->OnAttach();
    }

    void Application::OnStart() {
        VV_CORE_WARN("Started!");
        RenderAPI::SetAPI(RenderAPI::API::OpenGL);
    }

    void Application::Run() {
        while (true){

            {
                for (Layer *layer: m_LayerStack) {
                    layer->OnUpdate();

                    m_Window->OnUpdate();
                    m_Window->OnRender();
                }
            }
            m_ImGuiLayer->Begin();
            {
                for (Layer* layer : m_LayerStack)
                    layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();
        }
    }

    void Window::OnUpdate() {
        VV_CORE_INFO("GL Window Started!");
    }

    void Window::OnRender() {
// Draw a triangle
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);   // Red
        glVertex2f(0.0f, 0.5f);         // Top
        glColor3f(0.0f, 1.0f, 0.0f);   // Green
        glVertex2f(-0.5f, -0.5f);       // Bottom left
        glColor3f(0.0f, 0.0f, 1.0f);   // Blue
        glVertex2f(0.5f, -0.5f);        // Bottom right
        glEnd();
    }

}