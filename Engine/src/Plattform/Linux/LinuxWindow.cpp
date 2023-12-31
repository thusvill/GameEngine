//
// Created by bios on 10/3/23.
//

#include "LinuxWindow.h"
#include "../../Renderer/RenderAPI.h"
namespace VectorVertex {
    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char* description)
    {
        VV_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    LinuxWindow::LinuxWindow(const WindowProps& props)
    {
        Init(props);
    }

    LinuxWindow::~LinuxWindow()
    {
        Shutdown();
    }

    void LinuxWindow::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        VV_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (s_GLFWWindowCount == 0)
        {

            glfwSetErrorCallback(GLFWErrorCallback);
            if (!glfwInit())
            {
                VV_CORE_ERROR("Failed to initialize GLFW in LinuxWindow.cpp");
                return;
            }
            else{
                VV_CORE_INFO("GLFW Initialized successfully!");
            }
        }


            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
            ++s_GLFWWindowCount;

        VV_CORE_INFO("Window Created: {0}", props.Title);

        m_Context = GraphicsContext::Create(m_Window);
        m_Context->Init();

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(false);
        glViewport(0,0,(int)props.Width, (int)props.Height);
        Window::OnStart();


    }

    void LinuxWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
        VV_CORE_INFO("Destroyed {0}", m_Data.Title);
        --s_GLFWWindowCount;

        if (s_GLFWWindowCount == 0)
        {
            glfwTerminate();
        }
    }

    void LinuxWindow::OnUpdate()
    {
        if (s_GLFWWindowCount == 0)
        {
            VV_CORE_ERROR("GLFW is not initialized. Cannot proceed.");
            std::exit(0);
            return;
        }


        if (!glfwWindowShouldClose(m_Window))
        {
          glfwPollEvents();
          m_Context->SwapBuffers();
        }
        else
        {
            Shutdown();
        }
    }

    void LinuxWindow::OnRender() {
        Window::OnRender();
    }

    void LinuxWindow::OnStart() {

    }

    void LinuxWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool LinuxWindow::IsVSync() const
    {
        return m_Data.VSync;
    }

} // VectorVertex