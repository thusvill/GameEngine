//
// Created by bios on 9/30/23.
//

#include "Camera.h"
#include "RenderAPI.h"
#include "../Plattform/OpenGL/OpenGLCamera.h"
namespace VectorVertex {
    Scope<Camera> Camera::Create(VectorVertex::CameraProperties props) {
        switch (RenderAPI::GetAPI()) {
            case RenderAPI::API::None: VV_CORE_WARN("VectorVertex is currently not support for nonGraphicsAPI!"); return nullptr;
            case RenderAPI::API::OpenGL: return CreateScope<OpenGLCamera>(props);
        }
    }
} // VectorVertex