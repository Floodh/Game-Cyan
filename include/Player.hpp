#pragma once

#include "IDrawObject.hpp"
#include "GL_utilities.h"
#include "Camera.hpp"

class Player : public IDrawObject
{
    public:
        Player(Camera& camera);
        // Player(GLint* m, GLint* texture);
        ~Player();

        void Update();
        void Draw();

        void setPosition(const GLfloat x, const GLfloat y, const GLfloat z);


    private:
        Camera &camera;
        GLfloat* position;

        // Stats        
        int HP;
        int Points;

        GLuint shader;
        GLuint numVertices;
        GLfloat* pyramidVertices;
        GLfloat* colors;
        unsigned int vertexArrayObjID;
        
};