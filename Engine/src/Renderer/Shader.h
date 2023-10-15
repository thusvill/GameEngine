//
// Created by bios on 9/12/23.
//

#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include "string"
#include "../Core/Base.h"
namespace VectorVertex {

    class Shader {
    public:
        virtual ~Shader();

        virtual void Activate() const = 0;
        virtual void Delete() const = 0;
        virtual void* GetShader()=0;
        virtual unsigned int GetID()=0;
        static Ref<Shader> Create(const std::string &vertexFile,const std::string &fragmentFile,const std::string &geometryFile);
    };
}


#endif //GAMEENGINE_SHADER_H
