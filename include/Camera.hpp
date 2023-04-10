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
        //  return pointer to the projection matrix
        GLfloat* GetProjectionMatrix() const;

        //  update view matrix
        //  to avoid bugs, we should call this every frame
        void UpdateViewMatrix();

        void SetPosition(const GLfloat x, const GLfloat y, const GLfloat z);
        void SetLookAt(const GLfloat x, const GLfloat y, const GLfloat z);

        GLfloat* position;
        GLfloat* lookAtPosition;
        GLfloat* lookUpVector;

        //  DO NOT REINITILIZE THESE POINTERS, you can modify their content, but don't change where they points in memory
        GLfloat* const viewMatrix;
        GLfloat* const projectionMatrix;


};