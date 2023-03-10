#pragma once

#include "SDL.h"
#include "GL_utilities.h"

#include "IDrawObject.hpp"

#include <vector>


class GraphicUnit
{

    public:
        GraphicUnit(int windowWidth, int windowHeight); //  move code from main that initilizes the graphic here

        //  maybe merge Draw and Display?
        void Draw();
        void Display();
        //  Add draw object to Graphic unit, that object will then be drawn in the Draw function
        bool Add(IDrawObject *drawObject);

    private:

        //  
        int windowWidth, windowHeight;
        SDL_Window * window = nullptr;
        SDL_GLContext glContext = nullptr;

        std::vector<IDrawObject> drawObjects;

};