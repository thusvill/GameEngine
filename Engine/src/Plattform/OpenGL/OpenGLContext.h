//
// Created by bios on 9/30/23.
//

#ifndef GAMEENGINE_OPENGLCONTEXT_H
#define GAMEENGINE_OPENGLCONTEXT_H

#include "../../VectorVertex/Core.h"
#include "../../../vendor/glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
namespace VectorVertex {

    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };

} // VectorVertex

#endif //GAMEENGINE_OPENGLCONTEXT_H
