#pragma once

#include "SDL.h"
#include "GL_utilities.h"

#include "IDrawObject.hpp"
#include "Camera.hpp"

#include "Land.hpp"
#include "Water.hpp"
#include "TheSun.hpp"

//  read https://stackoverflow.com/questions/5751749/how-can-i-read-bmp-pixel-values-into-an-array

class Terrain : public IDrawObject
{
    public:

        //  the constructor should later receive the path to a .bmp file.
        
        Terrain() = delete;
        //  when we define the constructor, we also need to define all its members
        Terrain(Camera& camera, TheSun& theSun, uint8_t* levelData, const int levelWidth, const int levelHeight, GLfloat* const backgroundColor);
        void Draw() override;

    private:
    
        //  reference to camera
        Camera& camera;
        TheSun& theSun;

    public:

        //  land model
        Land land;
        //  water model
        Water water;



};