//
// Created by bios on 9/30/23.
//

#include "OpenGLContext.h"

namespace VectorVertex {

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
            : m_WindowHandle(windowHandle)
    {
    if(!windowHandle){
        VV_CORE_ERROR("OpenGL Graphics Context Null Window request!!");
    }
    }
    OpenGLContext::~OpenGLContext(){
    VV_CORE_WARN("GL Context Destroyed!");
    glfwTerminate();
    }

    void OpenGLContext::Init()
    {
        if(!m_WindowHandle){
            glfwTerminate();
            VV_CORE_ERROR("GLFW Window not found!");
            return;
        }

        glfwMakeContextCurrent(m_WindowHandle);
        if (!glfwGetCurrentContext()) {
            VV_CORE_ERROR("Failed to make GLFW context current");
            return;  // or handle the error accordingly
        }
        // Initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            VV_CORE_ERROR("Failed to initialize GLAD");
            glfwTerminate();
            return;
        }

        VV_CORE_INFO("GLFW made context!");
        VV_CORE_WARN("OpenGL Info:");
        VV_CORE_WARN("  Vendor: {0}", glGetString(GL_VENDOR));
        VV_CORE_WARN("  Renderer: {0}", glGetString(GL_RENDERER));
        VV_CORE_WARN("  Version: {0}", glGetString(GL_VERSION));

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            VV_CORE_ERROR("OpenGL error before rendering in GLContext: {}", error);
            VV_CORE_ASSERT(false, "Rendering error");
        } else{
            VV_CORE_INFO("OpenGL Context success!");
        }
    }

    void OpenGLContext::SwapBuffers()
    {
        //VV_CORE_INFO("Running SwapBuffer func in OpenGLContext!");
        glfwSwapBuffers(m_WindowHandle);
    }
}
// VectorVertex