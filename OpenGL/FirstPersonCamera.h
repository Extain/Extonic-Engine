#ifndef FIRST_PERSON_CAMERA_H
#define FIRST_PERSON_CAMERA_H

#include "Camera.h"

namespace Extonic {
	class FirstPersonCamera : public Camera
    {
    public:

        FirstPersonCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
            : Camera(position, up, yaw, pitch)
        {}
        FirstPersonCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
            : Camera(posX, posY, posZ, upX, upY, upZ, yaw, pitch)
        {}

        virtual void ProcessKeyboard(Camera_Movement direction, float deltaTime)
        {
            float velocity = MovementSpeed * deltaTime;
            if (direction == FORWARD)
            {
                Position.x += Front.x * velocity;
                Position.z += Front.z * velocity;
            }
                
            if (direction == BACKWARD)
            {
                Position.x -= Front.x * velocity;
                Position.z -= Front.z * velocity;
            }
            if (direction == LEFT)
                Position -= Right * velocity;
            if (direction == RIGHT)
                Position += Right * velocity;
            if (direction == UP)
                Position += Up * velocity;
            if (direction == DOWN)
                Position -= Up * velocity;
        }

        virtual void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
        {
            xoffset *= MouseSensitivity;
            yoffset *= MouseSensitivity;

            Yaw += xoffset;
            Pitch += yoffset;

            if (constrainPitch)
            {
                if (Pitch > 89.0f)
                    Pitch = 89.0f;
                if (Pitch < -89.0f)
                    Pitch = -89.0f;
            }
            updateCameraVectors();
        }

        virtual glm::mat4 GetViewMatrix()
        {
            return glm::lookAt(Position, Position + Front, Up);
        }

        void ProcessMouseScroll(float yoffset){ }
    };
}


#endif