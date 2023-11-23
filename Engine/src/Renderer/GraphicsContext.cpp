//
// Created by bios on 9/30/23.
//

#include "GraphicsContext.h"
#include "../Plattform/OpenGL/OpenGLContext.h"

namespace VectorVertex {
    Ref<GraphicsContext> GraphicsContext::Create(void* window)
    {
        switch (RenderAPI::GetAPI())
        {
            case RenderAPI::API::None:  return nullptr;
            case RenderAPI::API::OpenGL:  if(window!=NULL){
                return CreateRef<OpenGLContext>(static_cast<GLFWwindow*>(window));
            }
                else{
                    VV_CORE_ERROR("[GraphicsContext.cpp] NULL Window");
                    return nullptr;
                }
        }

        VV_CORE_ERROR("Unknown RendererAPI!");
        return nullptr;
    }
} // VectorVertex