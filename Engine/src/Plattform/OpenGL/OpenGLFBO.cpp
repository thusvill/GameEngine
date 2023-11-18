//
// Created by bios on 9/7/23.
//

#include "OpenGLFBO.h"
#include "iostream"
namespace VectorVertex{
    void CheckFBOErrors(){
        GLenum fbStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        //std::cerr << "Framebuffer status: " << fbStatus << std::endl;

        if (fbStatus != GL_FRAMEBUFFER_COMPLETE) {
            // Print a more informative error message based on the status
            switch (fbStatus) {
                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                    std::cerr << "Framebuffer incomplete: Attachment is NOT complete" << std::endl;
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                    std::cerr << "Framebuffer incomplete: No image is attached to the FBO" << std::endl;
                    break;
                case GL_FRAMEBUFFER_UNSUPPORTED:
                    std::cerr << "Framebuffer incomplete: Combination of internal formats used is not supported"
                              << std::endl;
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                    std::cerr << "Framebuffer incomplete: Multisample buffers for different attachments"
                              << std::endl;
                    break;
                default:
                    std::cerr << "Framebuffer incomplete: Unknown error" << std::endl;
                    break;
            }

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            throw std::runtime_error("Framebuffer is not complete.");
        }
    }
    OpenGLFBO::OpenGLFBO(int width, int height) : width(width), height(height) {
        // Create framebuffer object
        glGenFramebuffers(1, &framebufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);

        // Create texture attachment for color
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);

        // Create a renderbuffer object for depth and stencil attachment
        glGenRenderbuffers(1, &RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // Corrected format
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

        CheckFBOErrors();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }



    OpenGLFBO::~OpenGLFBO() {
        glDeleteFramebuffers(1, &framebufferID);
        glDeleteTextures(1, &textureID);
        VV_CORE_WARN("FBO Destroyed!");
    }

    void OpenGLFBO::Resize(int newWidth, int newHeight) {
        width = newWidth;
        height = newHeight;
        if(height <= 0){
            height = 800;
        }
        if(width <= 0){
            width = 800;
        }


        // Delete the previous framebuffer and texture
        glDeleteFramebuffers(1, &framebufferID);
        glDeleteTextures(1, &textureID);
        glDeleteRenderbuffers(1, &RBO);

        // Create a new framebuffer and texture with the updated size
        glGenFramebuffers(1, &framebufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
        // Create a renderbuffer object for depth and stencil attachment

        glGenRenderbuffers(1, &RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // Corrected format
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

        // Check for framebuffer completeness
        CheckFBOErrors();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }


    void OpenGLFBO::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
        glViewport(0, 0, width, height);
    }

    void OpenGLFBO::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // Reset the viewport to the default window size
        int screenWidth, screenHeight;
        glfwGetFramebufferSize(glfwGetCurrentContext(), &screenWidth, &screenHeight);
        glViewport(0, 0, screenWidth, screenHeight);
    }

}