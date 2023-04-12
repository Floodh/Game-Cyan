#pragma once

#include "SDL.h"
#include "GL_utilities.h"

#include "IDrawObject.hpp"
#include "Camera.hpp"
#include "Terrain.hpp"
#include "TheSun.hpp"

#include <vector>


//  master object that will handle mostly everything in the game world
//  this includes all 3d objects but not the UI
class World
{
    public:

        //  the constructor should later receive the path to a .bmp file.
        World();
        void Draw();
        void Update();

    private:
        std::vector<IDrawObject*> drawObjects;

    public:
        Camera camera;
        TheSun theSun;
        Terrain terrain;
        
        

};