#pragma once

#include "SDL.h"
#include <gl/gl.h>

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
            GLfloat* landmassVertices;
            GLuint shader;
    
};