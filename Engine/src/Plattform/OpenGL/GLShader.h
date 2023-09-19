//
// Created by bios on 9/7/23.
//
#pragma once
#ifndef GAMEENGINE_GLSHADER_H
#define GAMEENGINE_GLSHADER_H

#include "../../../vendor/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <string>
#include "../../Renderer/Shader.h"

namespace VectorVertex {
    std::string get_file_contents(const char* filename);

    class GLShader : public Shader{
    public:
        GLuint ID;
        GLShader(const std::string& vertexFile,const std::string& fragmentFile,const std::string& geometryFile);
        virtual ~GLShader();

        virtual void Activate() const override;
        virtual void Delete() const override;
    private:
        static void compileErrors(unsigned int shader, const char* type);
    };
}


#endif //GAMEENGINE_GLSHADER_H
