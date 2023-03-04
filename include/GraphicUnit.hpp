#pragma once

#include "SDL.h"
#include <windows.h>
#include <gl/gl.h>


class GraphicUnit{

    //SDL_Window* __cdecl window;
    public:
        void setup(const char window_name[]);
        void exit();
        void display();
        void proccesEvents();

    //private:
        SDL_Window* window; 
        SDL_Renderer* renderer;
        SDL_GLContext glContext;
        const int window_width = 1440;
        const int window_height = 1080;
};