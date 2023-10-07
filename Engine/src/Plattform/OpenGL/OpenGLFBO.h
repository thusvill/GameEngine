//
// Created by bios on 9/7/23.
//

#ifndef GAMEENGINE_OPENGLFBO_H
#define GAMEENGINE_OPENGLFBO_H
#include "../../Renderer/FrameBuffer.h"
#include "../../../vendor/glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "stdexcept"

namespace VectorVertex {
    class OpenGLFBO : public FrameBuffer {
    public:
        OpenGLFBO(int width, int height);

        ~OpenGLFBO();

        virtual void Resize(int newWidth, int newHeight) override;

        virtual void Bind() override;

        virtual void Unbind() override;

        virtual unsigned int GetRenderTexture() override{
            return static_cast<GLuint>(textureID);
        }


    private:
        GLuint framebufferID;
        GLuint textureID;
        int width;
        int height;
    };


}
#endif //GAMEENGINE_OPENGLFBO_H
