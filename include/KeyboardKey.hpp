#pragma once

#include "SDL.h"
#include "GL_utilities.h"

struct KeyboardKey
{
    //  delete to force proper initilization
    KeyboardKey() = delete; 
    //  keycode is mapped to key on keyboard
    KeyboardKey(SDL_Keycode keycode);

    SDL_Keycode keycode;    //  SDLK_*, check documentation(which does not exist anymore FFFFFFFFFFFFFFF!CK), is singed int tho
    bool keydown;
    bool keyup; 
    bool pressed;   //  if the most recent down event has not been followed by a up event
};