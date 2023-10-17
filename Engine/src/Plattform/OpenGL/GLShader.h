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
#include "glm/glm.hpp"
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


        virtual void SetInt(const std::string& name, int value) override;
        virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
        virtual void SetFloat(const std::string& name, float value) override;
        virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
        virtual void SetMat4(const std::string& name, const glm::mat4& value) override;


        void UploadUniformInt(const std::string& name, int value);
        void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

        void UploadUniformFloat(const std::string& name, float value);
        void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

        virtual const std::string& GetName() const override { return m_Name; }

    private:
        GLuint ID = 0;
        std::string m_Name;
        std::string m_FilePath;
        static void compileErrors(unsigned int shader, const char* type);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

        std::unordered_map<GLenum , std::string> m_GLSources;

        void Compile(std::unordered_map<GLenum, std::string> sources);
        std::string GetGLStateToString(GLenum state);
    };
}


#endif //GAMEENGINE_GLSHADER_H
