#include "Camera.hpp"

Camera::Camera()
    : 
        yaw{0.0}, pitch{0.5}, 
        maxPitch{1.45}, minPitch{1.45}, 
        x{0.25}, y{1.0}, z{0.0}, 
        lookAtX{0.0}, lookAtY{0.0}, lookAtZ{0.0}, 
        viewMatrix{new GLfloat[16]}
{
    this->UpdateViewMatrix();
}

GLfloat* Camera::GetViewMatrix() const
{
    return this->viewMatrix;
}

void Camera::UpdateViewMatrix()
{
    //  todo
    //  will need to use look at function to update the view matrix.

}
