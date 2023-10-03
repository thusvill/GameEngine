//
// Created by bios on 9/30/23.
//

#include "OpenGLContext.h"

namespace VectorVertex {

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
            : m_WindowHandle(windowHandle)
    {

    }

    void OpenGLContext::Init()
    {

        glfwMakeContextCurrent(m_WindowHandle);

        VV_CORE_INFO("OpenGL Info:");
        VV_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        VV_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        VV_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}
// VectorVertex