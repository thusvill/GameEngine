//
// Created by bios on 10/9/23.
//

#include "Model.h"
#include "RenderAPI.h"
#include "../Plattform/OpenGL/OpenGLModel.h"
namespace VectorVertex {
    Scope<Model> Model::Create(const char *file) {
        switch (RenderAPI::GetAPI()) {
            case RenderAPI::API::None: VV_CORE_WARN("VectorVertex is currently not support for nonGraphicsAPI!"); return nullptr;
            case RenderAPI::API::OpenGL: return CreateScope<OpenGLModel>(file);
        }
    }
} // VectorVertex