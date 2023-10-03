//
// Created by bios on 9/6/23.
//

#ifndef GAMEENGINE_APPLICATION_H
#define GAMEENGINE_APPLICATION_H

#include "Core.h"
#include "../Core/Log.h"
#include "../Renderer/RenderAPI.h"
#include "../Core/Window.h"

struct ApplicationSpecs{
    std::string Name = "VV App";
    std::string WorkingDirectory;
};

namespace VectorVertex {
    class Application {
    public:
        Application(const ApplicationSpecs& specs);

        virtual ~Application();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        virtual void OnStart();
        void Run();

        const ApplicationSpecs GetApplicationSpecificatons() const {return m_AppSpecs;}
    private:
        ApplicationSpecs m_AppSpecs;
        Scope<Window> m_Window;
        LayerStack m_LayerStack;

    };
    // To be defined in CLIENT
    Application* CreateApplication();
}

#endif //GAMEENGINE_APPLICATION_H
