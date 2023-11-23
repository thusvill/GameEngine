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
#include "../Editor/EditorLayer.h"

struct ApplicationSpecs{
    std::string Name = "VV App";
    std::string WorkingDirectory = "";
    int width=0, height =0;
};

namespace VectorVertex {
    class Application {
    public:
        Application(const ApplicationSpecs& specs);

        virtual ~Application()=default;

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        virtual void OnStart();
        void Run();
        void Stop();

        ImguiLayer* GetImGuiLayer()  {return m_ImGuiLayer;}
        ApplicationSpecs GetApplicationSpecificatons()  {return m_AppSpecs;}
        static Application& Get() { if(s_Instance){ return *s_Instance; }else{ VV_CORE_ERROR("No Application Found!");}}
        Window& GetWindow() { return *m_Window; }
        LayerStack GetLayerStack() {return m_LayerStack;}

        ImguiLayer* m_ImGuiLayer;
        EditorLayer* m_EditorLayer;
        bool DockSpaceEnabled = true;
        bool ExternalViewpoertsEnabled = false;
    private:
        friend Window;
        ApplicationSpecs m_AppSpecs;
        Ref<Window> m_Window;
        LayerStack m_LayerStack;
        static Application* s_Instance;

    };
    // To be defined in CLIENT
    Application* CreateApplication(ApplicationSpecs& specs);
}

#endif //GAMEENGINE_APPLICATION_H
