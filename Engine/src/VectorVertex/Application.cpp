//
// Created by bios on 9/6/23.
//

#include "Application.h"
#include "../Plattform/OpenGL/OpenGLVBO.h"
#include "../Plattform/OpenGL/OpenGLMesh.h"
namespace VectorVertex{
    Application* Application::s_Instance = nullptr;
    Application::Application(const ApplicationSpecs &specs): m_AppSpecs(specs) {

        if(!s_Instance) {
            s_Instance = this;
        }else{
            VV_CORE_ERROR("Application already exists!");
            return;
        }
        m_Window = Window::Create(WindowProps(m_AppSpecs.Name));
        m_ImGuiLayer = new ImguiLayer();
        PushOverlay(m_ImGuiLayer);

        m_EditorLayer = new EditorLayer();
        PushOverlay(m_EditorLayer);

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
                for (Layer *layer: m_LayerStack)
                    layer->OnRender();
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
    }

    void Window::OnUpdate() {
    }



    void Window::OnRender() {
        /*
        std::vector<GLVertex> vertices = {
                {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // Vertex 0 (position and color)
                {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},  // Vertex 1
                {glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}   // Vertex 2
        };

        std::vector<GLuint> indices = {
                0, 1, 2  // Indices to form a triangle
        };
        OpenGLTexture texture("","", 1);
        Scope<OpenGLMesh> triangleMesh = CreateScope<OpenGLMesh>(vertices, indices, {});
        //VectorVertex::OpenGLMesh triangleMesh(vertices, indices, {});
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        glm::vec3 translation = glm::vec3(0.0f);
        glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        glm::vec3 scale = glm::vec3(1.0f);

        Ref<Shader> shader = Shader::Create("default.vert","default.frag","default.geom") ;
        OpenGLCamera* camera = static_cast<OpenGLCamera*>(Application::Get().m_EditorLayer->GetEditorCamera().GetCamera());
// Call the Draw function
        triangleMesh.Draw(shader, camera, modelMatrix, translation, rotation, scale);
         */

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