//
// Created by bios on 9/7/23.
//

#include "GLShader.h"
namespace VectorVertex{
    std::string get_file_contents(const char* filename){
        std::ifstream in(filename, std::ios::binary);
        if(in){
            std::string contents;
            in.seekg(0,std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return(contents);
        }
        throw(errno);
    }

    GLShader::GLShader(const std::string& vertexFile,const std::string& fragmentFile,const std::string& geometryFile) {
#if defined(VV_DEBUG)
        VV_CORE_INFO("GL Shader createing {0}, {1}, {2}", vertexFile, fragmentFile, geometryFile);
#endif

        std::string vertexCode = get_file_contents(vertexFile.c_str());
        std::string fragmentCode = get_file_contents(fragmentFile.c_str());
        std::string geometryCode = get_file_contents(geometryFile.c_str());

        const char* vertexSource = vertexCode.c_str();
        const char* fragmentSource = fragmentCode.c_str();
        const char* geometrySource = geometryCode.c_str();

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader);
        compileErrors(vertexShader, "VERTEX");

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
        glCompileShader(fragmentShader);
        compileErrors(fragmentShader, "FRAGMENT");

        GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryShader, 1, &geometrySource, NULL);
        glCompileShader(geometryShader);
        compileErrors(geometryShader, "GEOMETRY");

        ID = glCreateProgram();

        glAttachShader(ID, vertexShader);
        glAttachShader(ID, geometryShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);
        compileErrors(ID, "PROGRAM");

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteShader(geometryShader);

#if defined(VV_DEBUG)
        VV_CORE_INFO("GL Shader Created ID:{0} : {1}, {2}, {3}",ID, vertexFile, fragmentFile, geometryFile);
#endif
    }


    void GLShader::Activate() const {
        glUseProgram(ID);
    }

    void GLShader::Delete() const{
        glDeleteProgram(ID);
    }

    void GLShader::compileErrors(unsigned int shader, const char *type) {
        GLint hasCompiled;
        char infoLog[1024];
        if(strcmp(type, "PROGRAM") != 0){
            glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
            if(hasCompiled == GL_FALSE){
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                VV_CORE_ERROR("Shader Compilation Error for: {0}, ID:{1}",type, shader);
            }
        } else{
            glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
            if(hasCompiled == GL_FALSE){
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                VV_CORE_ERROR("Shader Linking Error for: {0}, ID:{1}",type, shader);
            }
        }
    }
}