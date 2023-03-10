#pragma once

#include "SDL.h"
#include "GL_utilities.h"

#include "IDrawObject.hpp"

class Terrain : public IDrawObject
{
    public:

        //  the constructor should later receive the path to a .bmp file.
        //~Terrain() override = default;
        Terrain();
        void Draw() override;

    private:

        //  landmass model

        //  water model
            // vertex array object
            unsigned int vertexArrayObjID;
            unsigned int vertexBufferObjID;
            GLfloat* landmassVertices;
            GLuint shader;
    
};