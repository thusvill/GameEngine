//
// Created by bios on 9/11/23.
//

#ifndef GAMEENGINE_OPENGLTEXTURE_H
#define GAMEENGINE_OPENGLTEXTURE_H

#include "../../../vendor/glad/include/glad/glad.h"
#include "../../../vendor/stb/stb_image.h"

#include "GLShader.h"

namespace VectorVertex
{
class OpenGLTexture {
public:
    GLuint ID;
    const char*type;
    GLuint unit;
    OpenGLTexture(const char* image, const char* texType, GLuint slot);

    void texUni(GLShader& shader, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
};

}

#endif //GAMEENGINE_OPENGLTEXTURE_H
