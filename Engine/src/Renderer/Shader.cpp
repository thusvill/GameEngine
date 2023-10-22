//
// Created by bios on 9/12/23.
//

#include "RenderAPI.h"
#include "Shader.h"
#include "../Plattform/OpenGL/GLShader.h"
namespace VectorVertex{
    Ref<Shader>
    Shader::Create(const std::string name, const::std::string &vertexFile, const::std::string &fragmentFile, const::std::string &geometryFile) {
        switch (RenderAPI::GetAPI()) {
            case RenderAPI::API::None: VV_CORE_WARN("VectorVertex is currently not support for nonGraphicsAPI!"); return nullptr;
            case RenderAPI::API::OpenGL: return CreateRef<GLShader>(name, vertexFile,fragmentFile,geometryFile);
        }
        VV_CORE_ERROR("Unknown RendererAPI!");
        return nullptr;
    }
    Ref<Shader>
    Shader::Create(const std::string filepath) {
        switch (RenderAPI::GetAPI()) {
            case RenderAPI::API::None: VV_CORE_WARN("VectorVertex is currently not support for nonGraphicsAPI!"); return nullptr;
            case RenderAPI::API::OpenGL: return CreateRef<GLShader>(filepath);
        }
        VV_CORE_ERROR("Unknown RendererAPI!");
        return nullptr;
    }

    Shader::~Shader() noexcept {
        VV_CORE_WARN("Shader Destroyed!");
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
    {
        VV_CORE_INFO("Adding shader:{}", name);
        VV_CORE_ASSERT(!Exists(name), "Shader already exists!"+name);
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        auto& name = shader->GetName();
        Add(name, shader);
    }

    void ShaderLibrary::Update(const Ref<VectorVertex::Shader> shader) {
        const std::string name = shader->GetName();
        m_Shaders.find(name)->second = shader;
    }

    Ref<Shader> ShaderLibrary::Load(const::std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const::std::string& name, const::std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const::std::string& name)
    {
        VV_CORE_ASSERT(!Exists(name), "Shader not found!"+name);
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const::std::string& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}