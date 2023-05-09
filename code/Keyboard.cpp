#include "Keyboard.hpp"

#include <iostream>

using namespace std;

Keyboard::Keyboard()
{
    this->keys = vector<KeyboardKey>();
    this->keys.push_back((SDL_KeyCode)(1073741906));    //  up arrow
    this->keys.push_back((SDL_KeyCode)(1073741905));    //  down arrow
    this->keys.push_back((SDL_KeyCode)(1073741904));    //  right arrow
    this->keys.push_back((SDL_KeyCode)(1073741903));    //  left arrow
    //  add key bindings here
    this->keys.push_back((SDL_KeyCode)(119));           //  W
    this->keys.push_back((SDL_KeyCode)(115));           //  S
    this->keys.push_back((SDL_KeyCode)(97));            //  A
    this->keys.push_back((SDL_KeyCode)(100));           //  D

    this->keys.push_back((SDL_KeyCode)(1073742049));    //  shit
    this->keys.push_back((SDL_KeyCode)(32));    //  space
}

void Keyboard::HandleKeydown(const SDL_Keycode eventKey)
{
    //cout << "Keydown: " << eventKey << endl;
    for (long unsigned int i = 0; i < keys.size(); i++)
        if (keys[i].keycode == eventKey)
    {
        keys[i].keydown = true;
        keys[i].keypress = true;
        return;
    }
}


void Keyboard::HandleKeyup(const SDL_Keycode eventKey)
{
    cout << "Keyup: " << eventKey << endl;
    for (long unsigned int i = 0; i < keys.size(); i++)
        if (keys[i].keycode == eventKey)
    {
        keys[i].keyup = true;
        keys[i].keypress = false;
        return;
    }
}

void Keyboard::ClearFrameEvents()
{
    for (long unsigned int i = 0; i < keys.size(); i++)
    {
        keys[i].keydown = false;
        keys[i].keyup = false; 
    }
}

KeyboardKey Keyboard::GetKey(const SDL_Keycode key) const
{
    for (long unsigned int i = 0; i < keys.size(); i++)
        if (keys[i].keycode == key)
    {
        return keys[i];
    }

    throw "Invalid keycode, keycode has not been added in the constructor of the Keyboard class";
}
