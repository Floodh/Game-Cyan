#pragma once

#include "SDL.h"
#include "GL_utilities.h"

#include "KeyboardKey.hpp"


#include <vector>
#include <utility>  //  for std::pair

class Keyboard
{

    public:
        //  hardcode the bindings in this function
        Keyboard();
        //  SDL_Event is 56 bytes(but in practice only 8?, sdl2 seems to have padded the size for compiler compadibility)
        //  SDL_Event is union of several events such as SDL_KeyboardEvent
        //  check if event.type is equal to SDL_EventType::SDL_KEYDOWN or SDL_EventType::SDL_KEYUP
        //  check which key event.keysym.sym corresponds to which SDL_Keycode
        void HandleKeydown(const SDL_Keycode eventKey);
        void HandleKeyup(const SDL_Keycode eventKey);
        void ClearFrameEvents();

        //  returns copy of the key data, datastructure is small enough to be copied (we are coping the content of the keycode, for no good reason here, other than making the logic simpler)
        KeyboardKey GetKey(const SDL_Keycode key) const;

    private:

        std::vector<KeyboardKey> keys;       //  could make this a dictonary, but i think a vector is faster

        

        

};

