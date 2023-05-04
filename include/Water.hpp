#pragma once

#include "SDL.h"
#include "GL_utilities.h"

#include "IDrawObject.hpp"
#include "Camera.hpp"
#include "Player.hpp"

class Water : public IDrawObject
{
    public:

        //  the constructor should later receive the content of the .bmp file
        Water() = delete;
        Water(Camera& camera, uint8_t* levelData, int levelWidth, int levelHeight, GLfloat* const backgroundColor, int& frameCount);
        void Draw() override;

        Player* player = NULL;

        GLfloat* const backgroundColor;

    private:

        Camera& camera;         //  maybe only store pointer to viewMatrix instead?

        // vertex array object
        unsigned int vertexArrayObjID;

        unsigned int indexBufferObjID;
        unsigned int vertexBufferObjID;
        unsigned int colorBufferObjID;

        //  note
        //      we could potentialy make a buffer for the normals
        //      but it might be easier to send them in as a premade textures
        //      we will also probaly send in the offsets as textures aswell
        GLuint indexCount;
        GLuint vertexCount;    
        GLuint valueCount;

        GLfloat* vertices;
        GLfloat* colors;
        GLint* indices;
        
        GLuint shader;


        GLfloat* randomYPosition0; 
        GLfloat* randomYPosition1;
        int& frameCount;
    
};