//
// Created by bios on 9/6/23.
//

#include "Application.h"

namespace VectorVertex{
    Application::Application() {

    }
    Application::~Application() {
    }

    void Application::OnStart() {
        VV_CORE_WARN("Started!");
        RenderAPI::SetAPI(RenderAPI::API::OpenGL);

    }

    void Application::Run() {
        while (true);
    }

}