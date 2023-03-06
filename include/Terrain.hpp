#pragma once

#include "GL_utilities.h"

#include "SDL.h"


class Terrain
{
    public:

        //  the constructor should later receive the path to a .bmp file.
        Terrain();
        void Draw();

    private:

        //  landmass model

        //  water model
            // vertex array object
            unsigned int vertexArrayObjID;
            unsigned int vertexBufferObjID;
            GLfloat* landmassVertices;
            GLuint shader;
    
};