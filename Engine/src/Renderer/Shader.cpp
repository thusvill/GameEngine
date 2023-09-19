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
            case RenderAPI::API::None: std::cout<<"VectorVertex is currently not support for nonGraphicsAPI!"<<std::endl; return nullptr;
            case RenderAPI::API::OpenGL: return CreateRef<GLShader>(vertexFile,fragmentFile,geometryFile);
        }
        std::cout<<"Unknown RendererAPI!"<<std::endl;
        return nullptr;
    }
}