//
// Created by bios on 9/12/23.
//

#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include "../Core/Base.h"
#include <string>
#include "unordered_map"
namespace VectorVertex {

    class Shader {
    public:
        virtual ~Shader();

        virtual void Activate() const = 0;
        virtual void Delete() const = 0;
        virtual void* GetShader()=0;
        virtual unsigned int GetID()=0;

        virtual const std::string& GetName() const = 0;

        static Ref<Shader> Create(const std::string name, const std::string &vertexFile,const std::string &fragmentFile,const std::string &geometryFile);
        static Ref<Shader> Create(const std::string filepath);
    };

    class ShaderLibrary
    {
    public:
        void Add(const std::string& name, const Ref<Shader>& shader);
        void Add(const Ref<Shader>& shader);
        Ref<Shader> Load(const std::string& filepath);
        Ref<Shader> Load(const std::string& name, const std::string& filepath);

        Ref<Shader> Get(const std::string& name);

        bool Exists(const std::string& name) const;
    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };
}


#endif //GAMEENGINE_SHADER_H
