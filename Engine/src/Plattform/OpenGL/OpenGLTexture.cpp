//
// Created by bios on 9/11/23.
//

#include "OpenGLTexture.h"
#include "../../../vendor/stb/stb_image.h"
#include "../../Core/Log.h"
namespace VectorVertex{
    OpenGLTexture::OpenGLTexture(TextureData data): m_Data(data) {

#if defined(VV_DEBUG)
        VV_CORE_INFO("Texture Creating image: {0} , ID: {1}, Type: {2}, Slot: {3}", data.image, data.ID, data.type, data.unit);
#endif

                //Texture
        int widthImg, heightImg, numColCh;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* bytes = stbi_load(m_Data.image.c_str(), &widthImg, &heightImg, &numColCh, 0);

        if(!bytes){
            VV_CORE_ERROR("Creating Texture failed, null values found!");
            if(m_Data.image == ""){
                VV_CORE_ERROR(" Image data is null!");
            }
            if(heightImg<1){
                VV_CORE_ERROR(" Height value is {0}!", heightImg);
            }
            if(widthImg<1){
                VV_CORE_ERROR(" Width value is {0}!", widthImg);
            }
            if(numColCh>4){
                VV_CORE_ERROR(" Channel number is out of boundary, {}!", numColCh);
            }
            return;
        }

        glGenTextures(1, &m_Data.ID);
        glActiveTexture(GL_TEXTURE0+m_Data.unit);
        glBindTexture(GL_TEXTURE_2D, m_Data.ID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        //gl s t r = x y z
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        if(numColCh == 4){
            glTexImage2D
                    (
                            GL_TEXTURE_2D,
                            0,
                            GL_RGBA,
                            widthImg,
                            heightImg,
                            0,
                            GL_RGBA,
                            GL_UNSIGNED_BYTE,
                            bytes
                    );
        } else if(numColCh == 3){
            glTexImage2D
                    (
                            GL_TEXTURE_2D,
                            0,
                            GL_RGBA,
                            widthImg,
                            heightImg,
                            0,
                            GL_RGB,
                            GL_UNSIGNED_BYTE,
                            bytes
                    );
        } else if(numColCh == 1){
            glTexImage2D
                    (
                            GL_TEXTURE_2D,
                            0,
                            GL_RGBA,
                            widthImg,
                            heightImg,
                            0,
                            GL_RED,
                            GL_UNSIGNED_BYTE,
                            bytes
                    );
        } else{
            VV_CORE_ERROR("Automatic Texture type recognition failed {0}:{1}, defined type index: {2}",data.image, data.type, numColCh);
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(bytes);
        glBindTexture(GL_TEXTURE_2D, 0);
        VV_CORE_INFO("Texture: {} created! ", data.image);
    }

    void OpenGLTexture::texUni(Ref<Shader> _shader, const char* uniform, unsigned int unit) {
        //get texture uniforms
        _shader->Activate();
        GLuint texUni = glGetUniformLocation(_shader->GetID(), uniform);
        glUniform1i(texUni, unit);
        //VV_CORE_INFO("Added Texture Uniform: {}",uniform);

    }

    void OpenGLTexture::Bind() {
        glActiveTexture(GL_TEXTURE0+m_Data.unit);
        glBindTexture(GL_TEXTURE_2D, m_Data.ID);
    }

    void OpenGLTexture::Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLTexture::Delete() {
        glDeleteTextures(1, &m_Data.ID);
    }
}