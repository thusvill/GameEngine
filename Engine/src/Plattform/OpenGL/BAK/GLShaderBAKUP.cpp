//
// Created by bios on 9/7/23.
//

#include "GLShader.h"
#include "glm/gtc/type_ptr.hpp"
namespace VectorVertex{

    static GLenum ShaderTypeFromString(const std::string& type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;
        if (type == "geometry" || type == "geom")
            return GL_GEOMETRY_SHADER;

        VV_CORE_ASSERT(false, "Unknown shader type!");
        return 0;
    }

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
    GLShader::GLShader(const std::string filepath) :m_FilePath(filepath) {
        std::string source = get_file_contents(filepath.c_str());
        auto shaderSources = PreProcess(source);

        Compile(shaderSources);

        // Extract name from filepath
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);
        //Codes from Cherno
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
        m_GLSources[GL_VERTEX_SHADER] = vertexCode;
        m_GLSources[GL_FRAGMENT_SHADER] = fragmentCode;
        m_GLSources[GL_GEOMETRY_SHADER] = geometryCode;

        Compile(m_GLSources);

#if defined(VV_DEBUG)
        VV_CORE_INFO("GL Shader Created ID:{0} : {1}, {2}, {3}",ID, vertexFile, fragmentFile, geometryFile);
#endif
    }

    std::unordered_map<GLenum, std::string> GLShader::PreProcess(const std::string &source) {
        std::unordered_map<GLenum, std::string> shaderSources;

        const char* typeToken = "#shader";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
        while (pos != std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
            VV_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
            std::string type = source.substr(begin, eol - begin);
            VV_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

            size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
            VV_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
            pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

            shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
            //VV_CORE_WARN("Shader {0} :: {1}",type,shaderSources[ShaderTypeFromString(type)]);
        }

        return shaderSources;
    }

    void GLShader::Compile(std::unordered_map<GLenum, std::string> sources) {
        GLuint program = glCreateProgram();
        std::vector<GLuint> shaderIDs; //Use std::array it's fast than this!!
        shaderIDs.reserve(sources.size());
        for(auto&& [type, source] : sources){
            GLuint shader_created = glCreateShader(type);

            const char* sourcePtr = source.c_str();
            glShaderSource(shader_created, 1, &sourcePtr, NULL);

            glCompileShader(shader_created);
            compileErrors(shader_created, source,GetGLStateToString(type).c_str());

            glAttachShader(program, shader_created);
            shaderIDs.push_back(shader_created);
            GLenum err;
            if((err = glGetError()) != GL_NO_ERROR) {
                std::cerr << "Shader Compiling OpenGL Error: " << err << std::endl;
            }

        }
        glLinkProgram(program);
        compileErrors(program,"","PROGRAM");
        GLint isLinked;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked != GL_TRUE)
        {
            GLint maxLength;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());
            VV_CORE_ERROR("Shader linking failed ({0}):\n{1}", m_FilePath, infoLog.data());

            glDeleteProgram(program);

            for (auto id : shaderIDs)
                glDeleteShader(id);
        }

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
        VV_CORE_INFO("Shader {} Deactivated.", m_Name);
    }

    void GLShader::compileErrors(unsigned int shader,std::string src,const char *type) {
        GLint hasCompiled;
        char infoLog[1024];
        if(strcmp(type, "PROGRAM") != 0){
            glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
            if(hasCompiled == GL_FALSE){
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                VV_CORE_ERROR("Shader Compilation Error for: {0}, ID: {1}\n{2}", type, shader, infoLog);
                //VV_CORE_WARN("{0} source: {1}", type, src);
                VV_CORE_ASSERT(false, "Shader Compilation failed!");
                return;
            }
        } else{
            glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
            if(hasCompiled == GL_FALSE){
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                VV_CORE_ERROR("Shader Linking Error for: {0}, ID:{1}",type, shader);
                return;
            }
        }
    }


    void GLShader::SetInt(const std::string& name, int value)
    {
        
        UploadUniformInt(name, value);
    }

    void GLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
    {
        UploadUniformIntArray(name, values, count);
    }

    void GLShader::SetFloat(const std::string& name, float value)
    {
        
        UploadUniformFloat(name, value);
    }

    void GLShader::SetFloat2(const std::string& name, const glm::vec2& value)
    {
        
        UploadUniformFloat2(name, value);
    }

    void GLShader::SetFloat3(const std::string& name, const glm::vec3& value)
    {
        
        UploadUniformFloat3(name, value);
    }

    void GLShader::SetFloat4(const std::string& name, const glm::vec4& value)
    {
        
        UploadUniformFloat4(name, value);
    }

    void GLShader::SetMat4(const std::string& name, const glm::mat4& value){
        UploadUniformMat4(name, value);
    }

    void GLShader::UploadUniformInt(const std::string& name, int value)
    {
        GLint location = glGetUniformLocation(ID, name.c_str());
        glUniform1i(location, value);
    }

    void GLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
    {
        GLint location = glGetUniformLocation(ID, name.c_str());
        glUniform1iv(location, count, values);
    }

    void GLShader::UploadUniformFloat(const std::string& name, float value)
    {
        GLint location = glGetUniformLocation(ID, name.c_str());
        glUniform1f(location, value);
    }

    void GLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
    {
        GLint location = glGetUniformLocation(ID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void GLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
    {
        GLint location = glGetUniformLocation(ID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void GLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
    {
        GLint location = glGetUniformLocation(ID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void GLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
    {
        GLint location = glGetUniformLocation(ID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void GLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        GLint location = glGetUniformLocation(ID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
        GLenum err;
        if((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "Compiling OpenGL Error: " << err << std::endl;
            //VV_CORE_ASSERT(false, "Error");
        }
    }
}