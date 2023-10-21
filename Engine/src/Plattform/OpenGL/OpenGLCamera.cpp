//
// Created by bios on 9/12/23.
//

#include "OpenGLCamera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "GLShader.h"
namespace VectorVertex{
    OpenGLCamera::OpenGLCamera(CameraProperties props){
        m_CameraProperties = props;
    }

    void OpenGLCamera::Resize(int n_width, int n_height) {
        m_CameraProperties.width  =n_width;
        m_CameraProperties.height = n_height;
        updateMatrix();
    }

    void OpenGLCamera::SetCameraMode(VectorVertex::CamMode newMode) {
        m_CameraProperties.mode = newMode;
        updateMatrix();
    }

    void OpenGLCamera::updateMatrix(){
        //fov = FOVdeg;
        //Camera::nearPlane = nearPlane;
        //Camera::farPlane = farPlane;
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        view = glm::lookAt(m_CameraProperties.Position, m_CameraProperties.Position + m_CameraProperties.Orientation, m_CameraProperties.Up);
        if(m_CameraProperties.mode == CamMode::Perspective){
            projection = glm::perspective(glm::radians(m_CameraProperties.fov), static_cast<float>(m_CameraProperties.width)/static_cast<float>(m_CameraProperties.height), m_CameraProperties.nearPlane, m_CameraProperties.farPlane);
        }else if(m_CameraProperties.mode == CamMode::Orthographic){
            projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, m_CameraProperties.nearPlane, m_CameraProperties.farPlane);
        }

        m_CameraProperties.cameraMatrix  = projection * view;

    }


    void OpenGLCamera::Matrix(Ref<Shader> i_shader, const char *uniform) {
                glUniformMatrix4fv(glGetUniformLocation(i_shader->GetID(), uniform),1 , GL_FALSE, glm::value_ptr(m_CameraProperties.cameraMatrix));

    }


    void OpenGLCamera::Inputs(GLFWwindow* window) {
        if(m_CameraProperties.enableControl) {
            // Handles key inputs
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                m_CameraProperties.Position += current_speed * m_CameraProperties.Orientation;

            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                m_CameraProperties.Position += current_speed * -glm::normalize(glm::cross(m_CameraProperties.Orientation, m_CameraProperties.Up));

            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                m_CameraProperties.Position += current_speed * -m_CameraProperties.Orientation;

            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                m_CameraProperties.Position += current_speed * glm::normalize(glm::cross(m_CameraProperties.Orientation, m_CameraProperties.Up));

            }
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
                m_CameraProperties.Position += current_speed * m_CameraProperties.Up;

            }
            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
                m_CameraProperties.Position += current_speed * -m_CameraProperties.Up;

            }
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
                current_speed = m_CameraProperties.speed * 4;
            } else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
                current_speed = m_CameraProperties.speed;
            }



            // Handles mouse inputs
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
                // Hides mouse cursor
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

                // Prevents camera from jumping on the first click
                if (firstClick) {
                    glfwSetCursorPos(window, (m_CameraProperties.width / 2), (m_CameraProperties.height / 2));
                    firstClick = false;
                }

                // Stores the coordinates of the cursor
                double mouseX;
                double mouseY;
                // Fetches the coordinates of the cursor
                glfwGetCursorPos(window, &mouseX, &mouseY);

                // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
                // and then "transforms" them into degrees
                float rotX = m_CameraProperties.sensitivity * (float) (mouseY - (m_CameraProperties.height / 2)) / m_CameraProperties.height;
                float rotY = m_CameraProperties.sensitivity * (float) (mouseX - (m_CameraProperties.width / 2)) / m_CameraProperties.width;

                // Calculates upcoming vertical change in the m_CameraProperties.Orientation
                glm::vec3 newOrientation = glm::rotate(m_CameraProperties.Orientation, glm::radians(-rotX),
                                                       glm::normalize(glm::cross(m_CameraProperties.Orientation, m_CameraProperties.Up)));

                // Decides whether or not the next vertical m_CameraProperties.Orientation is legal or not
                if (abs(glm::angle(newOrientation, m_CameraProperties.Up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
                    m_CameraProperties.Orientation = newOrientation;
                    //std::cout << "Rotation x: "<< newOrientation.x<< " y: "<< newOrientation.y<< " z: "<< newOrientation.z << std::endl;
                }

                // Rotates the m_CameraProperties.Orientation left and right
                m_CameraProperties.Orientation = glm::rotate(m_CameraProperties.Orientation, glm::radians(-rotY), m_CameraProperties.Up);

                // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
                glfwSetCursorPos(window, (m_CameraProperties.width / 2), (m_CameraProperties.height / 2));
            } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
                // Unhides cursor since camera is not looking around anymore
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                // Makes sure the next time the camera looks around it doesn't jump
                firstClick = true;
            }
        }else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}