//
// Created by bios on 10/9/23.
//

#include "Texture.h"
#include "RenderAPI.h"
#include "../Plattform/OpenGL/OpenGLTexture.h"
namespace VectorVertex {
    Ref<Texture> Texture::Create(VectorVertex::TextureData data) {
        switch (RenderAPI::GetAPI()) {
            case RenderAPI::API::None: VV_CORE_WARN("VectorVertex is currently not support for nonGraphicsAPI!"); return nullptr;
            case RenderAPI::API::OpenGL: return CreateRef<OpenGLTexture>(data);
        }
        VV_CORE_ERROR("Unknown RendererAPI!");
        return nullptr;
    }
/*
    void TextureLibrary::Add(const std::string name, const std::string file_path) {
        TextureData data;
        data.image = file_path.c_str();
        Ref<Texture> tex = Texture::Create(data);
        tex->GetData().name = name;
    }
    void TextureLibrary::Add(Ref<VectorVertex::Texture> texture) {
        if(!Exists(texture->GetData().name)){
            m_Textures[texture->GetData().name] = texture;
        }else{
            VV_CORE_WARN("Texture {0} already exists!", texture->GetData().name);
        }
    }
    bool TextureLibrary::Exists(std::string name) {
        return m_Textures.find(name) != m_Textures.end();
    }
    Ref<Texture> TextureLibrary::Get(std::string name) {
        VV_CORE_ASSERT(!Exists(name), "Texture not found!");
        return m_Textures[name];
    }

    void TextureLibrary::Delete(const std::string name) {
        if(Exists(name)) {
            m_Textures[name]->Delete();
            m_Textures.erase(name);
        }
    }

    void TextureLibrary::Delete(Ref<VectorVertex::Texture> texture) {
        Delete(texture->GetData().name);
    }

    void TextureLibrary::DeleteAll() {
        for(auto& tex : m_Textures){
            m_Textures[tex.first]->Delete();
        }
        m_Textures.clear();
    }
*/
} // VectorVertex