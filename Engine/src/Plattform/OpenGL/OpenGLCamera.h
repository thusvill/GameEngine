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
#include "../../Renderer/Camera.h"

namespace VectorVertex{
    class OpenGLCamera : public Camera {

    public:
        CameraProperties m_CameraProperties;
        //OpenGLCamera(int width, int height, glm::vec3 position, float newfov, float newnp, float newfp);
        OpenGLCamera(CameraProperties props);
        bool firstClick = false;

        virtual void Resize(int n_width, int n_height) override;

        virtual void SetCameraMode(CamMode newMode) override;

        virtual void updateMatrix() override;

        virtual void Matrix(GLShader &shader, const char* uniform);

        virtual void Inputs(GLFWwindow *window) override;

        virtual void ApplyProperties(CameraProperties props) override{
            m_CameraProperties = props;
        }

        virtual CameraProperties GetProperties() override{
            return m_CameraProperties;
        }
        void LogLocation();

    public:
        float current_speed = m_CameraProperties.speed;
    };

}
#endif //GAMEENGINE_OPENGLCAMERA_H
