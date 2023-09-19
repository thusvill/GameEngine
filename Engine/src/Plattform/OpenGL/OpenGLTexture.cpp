//
// Created by bios on 9/11/23.
//

#include "OpenGLTexture.h"
namespace VectorVertex{
    OpenGLTexture::OpenGLTexture(const char *image, const char* texType, GLuint slot) {
        type = texType;
        //Texture
        int widthImg, heightImg, numColCh;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

        glGenTextures(1, &ID);
        glActiveTexture(GL_TEXTURE0+slot);
        glBindTexture(GL_TEXTURE_2D, ID);
        unit = slot;
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

    void OpenGLTexture::texUni(GLShader& shader, const char* uniform, GLuint unit) {
        //get texture uniforms
        GLuint texUni = glGetUniformLocation(shader.ID, uniform);
        shader.Activate();
        glUniform1i(texUni, unit);
    }

    void OpenGLTexture::Bind() {
        glActiveTexture(GL_TEXTURE0+unit);
        glBindTexture(GL_TEXTURE_2D, ID);
    }

    void OpenGLTexture::Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLTexture::Delete() {
        glDeleteTextures(1, &ID);
    }
}