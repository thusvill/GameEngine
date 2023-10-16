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

    std::string GLShader::GetGLStateToString(GLenum state) {
        switch (state) {
            case GL_VERTEX_SHADER: return "GL_VERTEX_SHADER";
            case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
            case GL_GEOMETRY_SHADER: return "GL_GEOMETRY_SHADER";
        }
        return nullptr;
    }

    GLShader::GLShader(const std::string name, const std::string& vertexFile,const std::string& fragmentFile,const std::string& geometryFile) {
#if defined(VV_DEBUG)
        VV_CORE_INFO("GL Shader createing {0}, {1}, {2}", vertexFile, fragmentFile, geometryFile);
#endif
        std::string vertexCode = get_file_contents(vertexFile.c_str());
        std::string fragmentCode = get_file_contents(fragmentFile.c_str());
        std::string geometryCode = get_file_contents(geometryFile.c_str());

        //const char* vertexSource = vertexCode.c_str();
        //const char* fragmentSource = fragmentCode.c_str();
        //const char* geometrySource = geometryCode.c_str();
        m_GLSources[GL_FRAGMENT_SHADER] = fragmentCode;
        m_GLSources[GL_VERTEX_SHADER] = vertexCode;
        m_GLSources[GL_GEOMETRY_SHADER] = geometryCode;

        CreateProgram(m_GLSources);

#if defined(VV_DEBUG)
        VV_CORE_INFO("GL Shader Created ID:{0} : {1}, {2}, {3}",ID, vertexFile, fragmentFile, geometryFile);
#endif
    }

    void GLShader::CreateProgram(std::unordered_map<GLenum, std::string> sources) {
        GLuint program = glCreateProgram();
        std::vector<GLuint> shaderIDs;
        for(auto&& [type, source] : sources){
            GLuint shader_created = shaderIDs.emplace_back(glCreateShader(GL_VERTEX_SHADER));

            const char* sourcePtr = source.c_str();
            glShaderSource(shader_created, 1, &sourcePtr, NULL);

            glCompileShader(shader_created);
            compileErrors(shader_created, GetGLStateToString(type).c_str());

            glAttachShader(program, shader_created);
        }
        glLinkProgram(program);
        compileErrors(program, "PROGRAM");

        for(auto id : shaderIDs){
            glDetachShader(program, id);
            glDeleteShader(id);
        }

        ID = program;

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