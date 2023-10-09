//
// Created by bios on 10/9/23.
//

#include "Texture.h"
#include "RenderAPI.h"
#include "../Plattform/OpenGL/OpenGLTexture.h"
namespace VectorVertex {
    Scope<Texture> Texture::Create(VectorVertex::TextureData data) {
        switch (RenderAPI::GetAPI()) {
            case RenderAPI::API::None: VV_CORE_WARN("VectorVertex is currently not support for nonGraphicsAPI!"); return nullptr;
            case RenderAPI::API::OpenGL: return CreateScope<OpenGLTexture>(data);
        }
        VV_CORE_ERROR("Unknown RendererAPI!");
        return nullptr;
    }
} // VectorVertex