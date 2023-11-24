//
// Created by bios on 9/12/23.
//
#pragma once
#ifndef GAMEENGINE_OPENGLCAMERA_H
#define GAMEENGINE_OPENGLCAMERA_H

#include "../../../vendor/glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "../../Renderer/Camera.h"
#include "../../Renderer/Shader.h"
#include "../../Core/Log.h"

namespace VectorVertex{
    class OpenGLCamera : public Camera {

    public:
        CameraProperties m_CameraProperties;
        //OpenGLCamera(int width, int height, glm::vec3 position, float newfov, float newnp, float newfp);
        OpenGLCamera(CameraProperties props);
        virtual ~OpenGLCamera(){}
        bool firstClick = false;

        virtual void Resize(int n_width, int n_height) override;

        virtual void SetCameraMode(CamMode newMode) override;

        virtual void updateMatrix() override;

        virtual void Matrix(Ref<Shader> i_shader, std::string uniform) override;

        virtual void Inputs(GLFWwindow *window) override;

        virtual void ApplyProperties(CameraProperties props) override{
            m_CameraProperties = props;
        }

        virtual CameraProperties GetProperties() override{
            return m_CameraProperties;
        }

        virtual void* GetCamera() override{
            return this;
        }
        void LogLocation();

    private:
        float current_speed = m_CameraProperties.speed;
    };

}
#endif //GAMEENGINE_OPENGLCAMERA_H
