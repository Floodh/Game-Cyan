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

    private:

        GLfloat yaw;
        GLfloat pitch;
        GLfloat maxPitch;
        GLfloat minPitch;

        GLfloat x, y, z;

        //  this matrix needs to be updated
        //  DO NOT REINTILIZE THIS POINTER, you can modify it, but don't change where it points in memory
        GLfloat* viewMatrix;



};