#pragma once

#include "SDL.h"
#include "GL_utilities.h"

#include "Player.hpp"
#include "VertexShape.hpp"

class Portal
{


    public:

        Portal(GLfloat x, GLfloat y, GLfloat z, Player& player, Camera& camera);
        void SetPosition(GLfloat x, GLfloat y, GLfloat z);
        void Draw();
        bool IsPlayerInside();

    private:

        Player& player;
        Camera& camera;

        VertexShape shape;

        GLfloat x,y,z;
        GLfloat* const transformMatrix;

};