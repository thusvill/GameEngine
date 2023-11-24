//
// Created by bios on 10/9/23.
//

#ifndef GAMEENGINE_TEXTURE_H
#define GAMEENGINE_TEXTURE_H
#include "Shader.h"
namespace VectorVertex {
    struct TextureData{
        unsigned int ID = 0;
        const char* type;
        unsigned int unit =0;
        std::string image = "";//path
        std::string name;
        TextureData() = default;
        TextureData(unsigned int id, std::string new_name):ID(id), name(new_name) {}
        TextureData(unsigned int id, std::string new_name, std::string path):ID(id), name(new_name), image(path) {}
        TextureData(std::string path, const char* type, unsigned int Unit):type(type), image(path),unit(Unit) {}
    };
    class Texture {
    public:
        virtual ~Texture()=default;

        virtual void texUni(Ref<Shader> _shader, std::string uniform, unsigned int unit)=0;
        virtual void Bind()=0;
        virtual void Unbind()=0;
        virtual void Delete()=0;
        virtual void* GetTexture()=0;
        virtual TextureData GetData()=0;

        static Ref<Texture>Create(TextureData data);

    };
/*
    class TextureLibrary{
    public:
        static void Add(const std::string name, const std::string file_path);
        static void Add(Ref<Texture> texture);
        static bool Exists(std::string name);
        static Ref<Texture> Get(std::string name);
        static void Delete(const std::string name);
        static void Delete(Ref<Texture> texture);
        static void DeleteAll();
    private:
        static std::unordered_map<std::string , Ref<Texture>> m_Textures;
    };
*/
} // VectorVertex

#endif //GAMEENGINE_TEXTURE_H
