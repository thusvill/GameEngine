//
// Created by bios on 10/5/23.
//

#ifndef GAMEENGINE_IMGUILAYER_H
#define GAMEENGINE_IMGUILAYER_H
#include "../Layer.h"
#include "../../VectorVertex/Application.h"
#include "../../../vendor/imgui/imgui.h"
#include "../../../vendor/imgui/imgui_internal.h"
#include "../../../vendor/imgui/imgui_impl_glfw.h"
#include "../../../vendor/imgui/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "../../../vendor/glad/include/glad/glad.h"
namespace VectorVertex {

    class ImguiLayer : public Layer {
    public:
        ImguiLayer();
        ~ImguiLayer() = default;

        virtual void OnAttach() {
            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
            //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
            //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

            float fontSize = 18.0f;// *2.0f;
            io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", fontSize);
            io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", fontSize);

            // Setup Dear ImGui style
            SetDarkThemeColors();
            //ImGui::StyleColorsClassic();

            // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
            ImGuiStyle& style = ImGui::GetStyle();
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                style.WindowRounding = 0.0f;
                style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            }

            ImGui::StyleColorsDark();

            Application& app = Application::Get();
            GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

            // Setup Platform/Renderer bindings
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 410");
        }
        virtual void OnDetach() {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }

        void Begin();
        void End();
        void SetDarkThemeColors();

        uint32_t GetActiveWidgetID() const;

    };

} // VectorVertex

#endif //GAMEENGINE_IMGUILAYER_H
