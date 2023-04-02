#pragma once
#include "SDL.h"
#include "GL_utilities.h"

#include "IDrawObject.hpp"


class Camera
{
    public:

        Camera();

        //  return pointer to its own view matrix
        GLfloat* GetViewMatrix() const;

        //  update view matrix
        //  to avoid bugs, we should call this every frame
        void UpdateViewMatrix();

        void SetPosition(const GLfloat x, const GLfloat y, const GLfloat z);
        void SetLookAt(const GLfloat x, const GLfloat y, const GLfloat z);

    private:

        GLfloat yaw;        //  left right
        GLfloat pitch;      //  up down
        GLfloat maxPitch;
        GLfloat minPitch;

        GLfloat* position;
        GLfloat* lookAtPosition;
        GLfloat* lookUpVector;


        //  this matrix needs to be updated
        //  DO NOT REINITILIZE THIS POINTER, you can modify it, but don't change where it points in memory
        GLfloat* viewMatrix;


        void LookAt();




};