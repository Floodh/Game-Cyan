#include "Camera.hpp"

//  specific to the cpp file
#define MAIN
#include "VectorUtils4.h"
#include "LittleOBJLoader.h"

#include "math.h"
#include "iostream"

using namespace std;

#define near 1.4
#define far 60.0
#define right 0.55
#define left -0.55
#define top 0.55
#define bottom -0.55

Camera::Camera(Mouse& mouse)
    : 
        viewMatrix{new GLfloat[16]},
        projectionMatrix{new GLfloat[16]{    	
            2.0f*near/(right-left), 0.0f, (right+left)/(right-left), 0.0f,
			0.0f, 2.0f*near/(top-bottom), (top+bottom)/(top-bottom), 0.0f,
			0.0f, 0.0f, -(far + near)/(far - near), -2*far*near/(far - near),
			0.0f, 0.0f, -1.0f, 0.0f }
        },
        mouse{mouse}
{
    this->position = new GLfloat[3]{35.0, 14.0, 5.0};
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

    GLfloat x, y, z;
    x = this->position[0], y = this->position[1], z = this->position[2];

    //  mouse dragMode
    if (mouseDragMode)
    {
        if (mouse.middle.keypress == false)
        {
            mouseDragMode = false;
        }
        else
        {
            // get mouse coordinates 
            GLfloat mouseX = (GLfloat)mouse.xRel;
            GLfloat mouseY = (GLfloat)mouse.yRel;

            if ((mouseX) != 0.0)
                radians -= mouseX * dragSpeedRad;

            if ((mouseY) != 0.0)
                radiansY += mouseY * dragSpeedY;

            GLfloat  lookX = this->lookAtPosition[0], lookY = this->lookAtPosition[1], lookZ = this->lookAtPosition[2];

            // calculate the camera's position
            x = lookX + 5.0f * sin(radians);    
            z = lookZ + 5.0f * cos(radians);
            y = lookY + 5.0f * sin(radiansY);   //  this makes the camera behave weird, but i can't think of the math to fix it

        }

    }
    else
    {
        if (mouse.middle.keydown)
        {
            mouseDragMode = true;
            this->radians = 3.5f;
            this->radiansY = 0.0f;
        }
    }


    mat4 result = lookAt(
        vec3(x, y, z),
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




