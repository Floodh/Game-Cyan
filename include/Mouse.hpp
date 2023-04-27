#pragma once

#include "SDL.h"
#include "GL_utilities.h"


struct MouseButton 
{
    MouseButton();
    bool keydown;
    bool keyup; 
    bool keypress;   //  if the most recent down event has not been followed by a up event    
};

class Mouse
{

    public:

        Mouse();
        void HandleMouseMotion(const SDL_MouseMotionEvent event);
        void HandleMouseButton(const SDL_MouseButtonEvent event);
        void ClearFrameEvents();

        Sint32 x, y;

        Sint32 xRel, yRel;
        

        MouseButton right;  //  3
        MouseButton middle; //  2
        MouseButton left;   //  1

};