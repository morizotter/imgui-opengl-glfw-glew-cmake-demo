#pragma once
#include <GL/glew.h>
#include <dependency/glm/glm/glm.hpp>
#include <dependency/glm/glm/gtc/matrix_transform.hpp>
#include <dependency/glm/glm/gtc/quaternion.hpp>
#include <dependency/glm/glm/gtx/quaternion.hpp>
#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::mat4 projection;
    glm::mat4 view;
    // constructor with vectors

private:
    quat MyQuaternion;
};
