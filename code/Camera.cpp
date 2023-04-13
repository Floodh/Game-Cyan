#include "Camera.hpp"

//  specific to the cpp file
#define MAIN
#include "VectorUtils4.h"

#define near 1.4
#define far 60.0
#define right 0.55
#define left -0.55
#define top 0.55
#define bottom -0.55

Camera::Camera()
    : 
        viewMatrix{new GLfloat[16]},
        projectionMatrix{new GLfloat[16]{    	
            2.0f*near/(right-left), 0.0f, (right+left)/(right-left), 0.0f,
			0.0f, 2.0f*near/(top-bottom), (top+bottom)/(top-bottom), 0.0f,
			0.0f, 0.0f, -(far + near)/(far - near), -2*far*near/(far - near),
			0.0f, 0.0f, -1.0f, 0.0f }
        }
{
    this->position = new GLfloat[3]{35.0, 17.0, 5.0};
    this->lookAtPosition = new GLfloat[3]{20.0, 0.0, 20};
    this->lookUpVector = new GLfloat[3]{0.0, 1.0, 0};

    this->UpdateViewMatrix();
}

GLfloat* Camera::GetViewMatrix() const
{
    return this->viewMatrix;
}
GLfloat* Camera::GetProjectionMatrix() const
{
    return this->projectionMatrix;
}

void Camera::UpdateViewMatrix()
{
    //  todo
    //  will need to use look at function to update the view matrix.
    mat4 result = lookAt(
        vec3(this->position[0], this->position[1], this->position[2]),
        vec3(this->lookAtPosition[0], this->lookAtPosition[1], this->lookAtPosition[2]),
        vec3(this->lookUpVector[0], this->lookUpVector[1], this->lookUpVector[2])
        );

    for (int i = 0; i < 16; i++)
    {
        this->viewMatrix[i] = result.m[i];
    }
    
    
}

void Camera::SetPosition(const GLfloat x, const GLfloat y, const GLfloat z)
{
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
}
void Camera::SetLookAt(const GLfloat x, const GLfloat y, const GLfloat z)
{
    this->lookAtPosition[0] = x;
    this->lookAtPosition[1] = y;
    this->lookAtPosition[2] = z;    
}




