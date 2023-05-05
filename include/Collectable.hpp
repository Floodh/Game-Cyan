#pragma once

#include "SDL.h"
#include "GL_utilities.h"

#include "Player.hpp"
#include "VertexShape.hpp"


class Collectable
{

    public:

        Collectable(GLfloat x, GLfloat y, GLfloat z, Player& player, Camera& camera, GLfloat* color, GLfloat* backgroundColor);
        void SetPosition(GLfloat x, GLfloat y, GLfloat z);
        void Draw();
        bool IsPlayerInside();

        bool canBeCollected = true;
        bool isCollected = false;

    private:

        Player& player;
        Camera& camera;

        VertexShape shape;

        GLfloat x,y,z;
        GLfloat* const transformMatrix;


};