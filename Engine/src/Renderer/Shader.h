//
// Created by bios on 9/12/23.
//

#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include "string"
#include "RenderAPI.h"
#include "../Core/Base.h"
namespace VectorVertex {

    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void Activate() const = 0;
        virtual void Delete() const = 0;

        static Ref<Shader> Create(const std::string &vertexFile,const std::string &fragmentFile,const std::string &geometryFile);
    };
}


#endif //GAMEENGINE_SHADER_H
