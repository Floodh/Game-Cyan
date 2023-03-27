#include "Keyboard.hpp"

#include <iostream>

using namespace std;

Keyboard::Keyboard()
{
    this->keys = vector< pair<char,KeyboardKey> >();
    //  add key bindings here
}

void Keyboard::HandleKeydown(const SDL_Keycode& event)
{
    cout << "Keydown: " << event << endl;
}


void Keyboard::HandleKeyup(const SDL_Keycode& event)
{
    cout << "Keyup: " << event << endl;
}