#pragma once

#include "SDL.h"
#include "GL_utilities.h"

#include "IDrawObject.hpp"
#include "Camera.hpp"

class Water : public IDrawObject
{
    public:

        //  the constructor should later receive the content of the .bmp file
        Water() = delete;
        Water(Camera& camera);
        void Draw() override;

    private:

        Camera& camera;

        // vertex array object
        unsigned int vertexArrayObjID;

        unsigned int vertexBufferObjID;
        unsigned int colorBufferObjID;

        GLfloat* vertices;
        GLfloat* colors;
        
        GLuint shader;
    
};