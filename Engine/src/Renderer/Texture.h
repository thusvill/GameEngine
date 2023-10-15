//
// Created by bios on 10/9/23.
//

#ifndef GAMEENGINE_TEXTURE_H
#define GAMEENGINE_TEXTURE_H
#include "Shader.h"
namespace VectorVertex {
    struct TextureData{
        unsigned int ID = 0;
        const char*type;
        unsigned int unit =0;
        std::string image = "";
    };
    class Texture {
    public:
        virtual ~Texture()=default;

        virtual void texUni(Shader* _shader, const char * uniform, unsigned int unit)=0;
        virtual void Bind()=0;
        virtual void Unbind()=0;
        virtual void Delete()=0;
        virtual void* GetTexture()=0;
        virtual TextureData GetData()=0;

        static Scope<Texture>Create(TextureData data);

    };

} // VectorVertex

#endif //GAMEENGINE_TEXTURE_H
