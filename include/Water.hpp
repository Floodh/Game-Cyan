#pragma once

#include "SDL.h"
#include "GL_utilities.h"

#include "IDrawObject.hpp"

class Water : public IDrawObject
{
    public:

        //  the constructor should later receive the content of the .bmp file
        Water();
        void Draw() override;

    private:

        // vertex array object
        unsigned int vertexArrayObjID;
        unsigned int vertexBufferObjID;
        GLfloat* landmassVertices;
        GLuint shader;
    
};