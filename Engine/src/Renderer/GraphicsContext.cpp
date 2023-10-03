//
// Created by bios on 9/30/23.
//

#include "GraphicsContext.h"
#include "../Plattform/OpenGL/OpenGLContext.h"

namespace VectorVertex {
    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
        switch (RenderAPI::GetAPI())
        {
            case RenderAPI::API::None:  return nullptr;
            case RenderAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        }

        VV_CORE_ERROR("Unknown RendererAPI!");
        return nullptr;
    }
} // VectorVertex