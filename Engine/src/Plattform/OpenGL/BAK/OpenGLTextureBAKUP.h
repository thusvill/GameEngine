//
// Created by bios on 9/11/23.
//

#ifndef GAMEENGINE_OPENGLTEXTURE_H
#define GAMEENGINE_OPENGLTEXTURE_H

#include "../../../vendor/glad/include/glad/glad.h"
#include "GLShader.h"
#include "../../Renderer/Texture.h"

namespace VectorVertex
{
    class OpenGLTexture : public Texture {
public:

    OpenGLTexture(TextureData data);
    virtual ~OpenGLTexture(){
        Delete();
    }

    virtual void texUni(Ref<Shader> _shader, const char* uniform, unsigned int unit) override;
    virtual void Bind() override;
    virtual void Unbind() override;
    virtual void Delete() override;
    virtual void* GetTexture() override{
        return this;
    }
    virtual TextureData GetData() override{
        return m_Data;
    }
private:
    TextureData m_Data;
};

}

#endif //GAMEENGINE_OPENGLTEXTURE_H
