//
// Created by bios on 9/6/23.
//

#ifndef GAMEENGINE_APPLICATION_H
#define GAMEENGINE_APPLICATION_H

#include "Core.h"
#include "../Core/Log.h"
#include "../Renderer/RenderAPI.h"
#include "../Core/Window.h"
#include "../Core/LayerStack.h"
#include "../ImGuiLayer/ImguiLayer.h"

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

        ImguiLayer* GetImGuiLayer()  {return m_ImGuiLayer;}
        ApplicationSpecs GetApplicationSpecificatons()  {return m_AppSpecs;}
        static Application& Get() { return *s_Instance; }
        Window& GetWindow() { return *m_Window; }
        ImguiLayer* m_ImGuiLayer;
    private:
        ApplicationSpecs m_AppSpecs;
        Scope<Window> m_Window;
        LayerStack m_LayerStack;
        static Application* s_Instance;

    };
    // To be defined in CLIENT
    Application* CreateApplication(ApplicationSpecs& specs);
}

#endif //GAMEENGINE_APPLICATION_H
