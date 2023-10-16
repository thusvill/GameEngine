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
        GLShader(const std::string name, const std::string& vertexFile,const std::string& fragmentFile,const std::string& geometryFile);
        GLShader(const std::string filepath);
        virtual ~GLShader() override{
            VV_CORE_WARN("GLShader Destroyed!");
            Delete();
        }
        virtual void Activate() const override;
        virtual void Delete() const override;
        virtual void* GetShader() override{
            return this;
        }
        virtual unsigned int GetID() override{
            return ID;
        }

        virtual const std::string& GetName() const override { return m_Name; }

    private:
        GLuint ID = 0;
        std::string m_Name;
        std::string m_FilePath;
        static void compileErrors(unsigned int shader, const char* type);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

        std::unordered_map<GLenum , std::string> m_GLSources;

        void CreateProgram(std::unordered_map<GLenum, std::string> sources);
        std::string GetGLStateToString(GLenum state);
    };
}


#endif //GAMEENGINE_GLSHADER_H
