//
// Created by bios on 9/7/23.
//

#ifndef GAMEENGINE_GLSHADER_H
#define GAMEENGINE_GLSHADER_H

#include "../../../vendor/glad/include/glad/glad.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <GLFW/glfw3.h>

namespace VectorVertex {
    std::string get_file_contents(const char* filename);
    class GLShader {
        GLuint ID;
        GLShader(const char* vertexFile, const char* fragmentFile, const char* geometryFile);

        void Activate();
        void Delete();
    private:
        void compileErrors(unsigned int shader, const char* type);
    };
}


#endif //GAMEENGINE_GLSHADER_H
