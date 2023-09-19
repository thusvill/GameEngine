//
// Created by bios on 9/12/23.
//

#ifndef GAMEENGINE_OPENGLCAMERA_H
#define GAMEENGINE_OPENGLCAMERA_H

#include "../../../vendor/glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "GLShader.h"

namespace VectorVertex{
class OpenGLCamera {

public:
    enum class CamMode {
        Perspective,
        Orthographic
    };

    CamMode mode = CamMode::Perspective;

    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 cameraMatrix = glm::mat4(1.0f);

    bool firstClick = true;

    int width;
    int height;

    float speed = 0.005f;
    float sensitivity = 100.0f;
    bool enableControl = false;

    OpenGLCamera(int width, int height, glm::vec3 position, float newfov, float newnp, float newfp);

    void Resize(int n_width, int n_height);

    void SetCameraMode(CamMode newMode);

    void updateMatrix();

    void Matrix(GLShader &shader, const char *uniform);

    void Inputs(GLFWwindow *window);

    void LogLocation();

    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 1000.0f;
public:
    float current_speed = speed;
};

}
#endif //GAMEENGINE_OPENGLCAMERA_H
