//
// Created by bios on 10/5/23.
//

#include "ImguiLayer.h"
#include "../VectorVertex/Application.h"
#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/imgui_internal.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"
#include "../../vendor/imgui/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

namespace VectorVertex {

    bool initializedImGui = false;  // Flag to track initialization status

// Function to initialize ImGui and related components
    void InitializeImGui(GLFWwindow* window) {
        if (!initializedImGui) {
            // Initialize ImGui for GLFW
            ImGui_ImplGlfw_InitForOpenGL(window, true);

            // Initialize ImGui for OpenGL
            ImGui_ImplOpenGL3_Init("#version 330 core");

            // Set the flag to true to indicate initialization
            initializedImGui = true;
        }
    }

    ImguiLayer::ImguiLayer() : Layer("ImGuiLayer") {

    }
    void ImguiLayer::OnAttach(){
        // Setup Dear ImGui context
        //IMGUI_CHECKVERSION();

        //if(!ImGui::GetCurrentContext()) {
            VV_CORE_INFO("Imgui Creating Context...");
            ImGui::CreateContext();
            VV_CORE_INFO("Imgui Created Context!");
        //}

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;



        // Setup Dear ImGui style
        //SetDarkThemeColors();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();

        Application& app = Application::Get();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

        // Setup Platform/Renderer bindings
        InitializeImGui(window);
    }
    void ImguiLayer::OnDetach(){
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            //ImGui::Shutdown();
            initializedImGui = false;
#if defined(VV_DEBUG)
            VV_CORE_INFO("Imgui Detached!");
#endif
        }
    }
    void ImguiLayer::Begin() {

        if (ImGui::GetCurrentContext() == nullptr) {
            VV_CORE_CRITICAL("ImGui Context not found!");
            return;
        }
        if(!initializedImGui){
            VV_CORE_ERROR("Imgui Plattform not Initilized");
            return;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImguiLayer::End() {
        ImGuiIO &io = ImGui::GetIO();
        Application &app = Application::Get();
        io.DisplaySize = ImVec2((float) app.GetWindow().GetWidth(), (float) app.GetWindow().GetHeight());

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImguiLayer::SetDarkThemeColors()
        {
            auto& colors = ImGui::GetStyle().Colors;
            colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

            // Headers
            colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
            colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
            colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

            // Buttons
            colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
            colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
            colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

            // Frame BG
            colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
            colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
            colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

            // Tabs
            colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
            colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
            colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

            // Title
            colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        }

    uint32_t ImguiLayer::GetActiveWidgetID() const
        {
            return GImGui->ActiveId;
        }



} // VectorVertex