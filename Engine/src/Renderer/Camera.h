//
// Created by bios on 9/30/23.
//

#ifndef GAMEENGINE_CAMERA_H
#define GAMEENGINE_CAMERA_H
#include "Shader.h"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
namespace VectorVertex {
    enum class CamMode {
        Perspective,
        Orthographic
    };
    struct CameraProperties{
        CamMode mode = CamMode::Perspective;
        float fov = 45.0f;
        float nearPlane = 0.1f;
        float farPlane = 1000.0f;
        int width = 800;
        int height = 800;
        float speed = 0.005f;
        float sensitivity = 100.0f;
        bool enableControl = true;
        glm::vec3 Position;
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 cameraMatrix = glm::mat4(1.0f);
    };

    class Camera {
    public:
        virtual ~Camera() = default;

        virtual void updateMatrix()=0;
        virtual void Matrix(Shader *i_shader, const char* uniform)=0;
        virtual void Inputs(GLFWwindow* window)=0;
        virtual void SetCameraMode(CamMode newMode)=0;

        virtual void Resize(int n_width, int n_height)=0;
        virtual void ApplyProperties(CameraProperties props)=0;
        virtual CameraProperties GetProperties() = 0;
        virtual void* GetCamera()=0;

        static Scope<Camera> Create(CameraProperties props);

    };

} // VectorVertex

#endif //GAMEENGINE_CAMERA_H
