#pragma once

#include "SDL.h"
#include "GL_utilities.h"

#include "IDrawObject.hpp"
#include "Camera.hpp"
#include "TheSun.hpp"


class Land : public IDrawObject
{
    public:

        //  the constructor should later receive the content of the .bmp file
        Land() = delete;
        Land(Camera& camera, TheSun& theSun);
        void Draw() override;

    private:

        Camera& camera;         //  maybe only store pointer to viewMatrix instead?
        TheSun& theSun;

        // vertex array object
        unsigned int vertexArrayObjID;

        unsigned int indexBufferObjID;
        unsigned int vertexBufferObjID;
        unsigned int colorBufferObjID;
        unsigned int normalBufferObjID;

        //  note
        //      we could potentialy make a buffer for the normals
        //      but it might be easier to send them in as a premade textures
        //      we will also probaly send in the offsets as textures aswell
        GLuint indexCount;
        GLuint vertexCount;    
        GLuint valueCount;

        GLfloat* vertices;
        GLfloat* colors;
        GLfloat* normals;
        GLint* indices;
        
        GLuint shader;
    
};