#pragma once


#include "GL_utilities.h"
#include "Camera.hpp"

class Player
{
    public:
        Player(Camera& camera);
        // Player(GLint* m, GLint* texture);
        ~Player();

        void Update();
        void Draw();


    private:
        Camera &camera;
        int HP;
        int Points;
};