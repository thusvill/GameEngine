//
// Created by bios on 9/11/23.
//

#include "OpenGLTexture.h"
namespace VectorVertex{
    OpenGLTexture::OpenGLTexture(TextureData data): m_Data(data) {
                //Texture
        int widthImg, heightImg, numColCh;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* bytes = stbi_load(m_Data.image, &widthImg, &heightImg, &numColCh, 0);

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
            throw std::invalid_argument("Automatic Texture type recognition failed!");
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(bytes);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLTexture::~OpenGLTexture() noexcept {
        Delete();
    }
    void OpenGLTexture::texUni(Shader* _shader, const char* uniform, unsigned int unit) {
        //get texture uniforms
        GLShader* shader = static_cast<GLShader*>(_shader->GetShader());
        GLuint texUni = glGetUniformLocation(shader->ID, uniform);
        shader->Activate();
        glUniform1i(texUni, unit);
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