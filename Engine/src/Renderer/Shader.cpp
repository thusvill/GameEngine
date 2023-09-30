//
// Created by bios on 9/12/23.
//

#include "Shader.h"
#include "RenderAPI.h"
#include "../Plattform/OpenGL/GLShader.h"
namespace VectorVertex{
    Ref<Shader>
    Shader::Create(const std::string &vertexFile, const std::string &fragmentFile, const std::string &geometryFile) {
        switch (RenderAPI::GetAPI()) {
            case RenderAPI::API::None: VV_CORE_WARN("VectorVertex is currently not support for nonGraphicsAPI!"); return nullptr;
            case RenderAPI::API::OpenGL: return CreateRef<GLShader>(vertexFile,fragmentFile,geometryFile);
        }
        VV_CORE_ERROR("Unknown RendererAPI!");
        return nullptr;
    }
}