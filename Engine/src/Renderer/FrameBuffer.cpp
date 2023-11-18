//
// Created by bios on 10/6/23.
//

#include "FrameBuffer.h"
#include "../Plattform/OpenGL/OpenGLFBO.h"
namespace VectorVertex {
    Ref<FrameBuffer> FrameBuffer::Create(int width, int height) {
        switch (RenderAPI::GetAPI()) {
            case RenderAPI::API::None: VV_CORE_WARN("VectorVertex is currently not support for nonGraphicsAPI!"); return nullptr;
            case RenderAPI::API::OpenGL: return CreateRef<OpenGLFBO>(static_cast<int>(width), static_cast<int>(height));
        }
        VV_CORE_ERROR("Unknown RendererAPI!");
        return nullptr;
    }
} // VectorVertex