//
// Created by bios on 9/6/23.
//

#include "Application.h"

namespace VectorVertex{
    Application::Application(const ApplicationSpecs &specs): m_AppSpecs(specs) {
        m_Window = Window::Create(WindowProps(m_AppSpecs.Name));

    }
    Application::~Application() {
    }

    void Application::PushLayer(VectorVertex::Layer *layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(VectorVertex::Layer *layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnStart() {
        VV_CORE_WARN("Started!");
        RenderAPI::SetAPI(RenderAPI::API::OpenGL);
    }

    void Application::Run() {
        while (true){

            for(Layer* layer : m_LayerStack){
                layer->OnUpdate();
                m_Window->OnUpdate();
            }
        }
    }

    void Window::OnUpdate() {
        VV_CORE_INFO("GL Window Started!");
    }

}