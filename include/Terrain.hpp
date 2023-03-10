#pragma once

#include "SDL.h"
#include "GL_utilities.h"

// #include "GL_utilities.h"
// #include "SDL.h"
// #include "SDL_opengl.h"
// #include <GL/gl.h>

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