//
// Created by bios on 9/7/23.
//

#ifndef GAMEENGINE_OPENGLFBO_H
#define GAMEENGINE_OPENGLFBO_H
#include "../../../vendor/glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "stdexcept"
namespace VectorVertex {
    class OpenGLFBO {
    public:
        OpenGLFBO(int width, int height);

        ~OpenGLFBO();

        void Resize(int newWidth, int newHeight);

        void Bind();

        void Unbind();

        GLuint GetTexture() const;

    private:
        GLuint framebufferID;
        GLuint textureID;
        int width;
        int height;
    };


}
#endif //GAMEENGINE_OPENGLFBO_H
