#include "Mouse.hpp"


#include "iostream"
using namespace std;

MouseButton::MouseButton()
    :
        keydown{false},
        keyup{false},
        keypress{false}
{}


Mouse::Mouse()
    :   
        right{},
        middle{},
        left{}
{}


void Mouse::HandleMouseMotion(const SDL_MouseMotionEvent event)
{
    this->x = event.x;
    this->y = event.y;

    this->xRel = event.xrel;
    this->yRel = event.yrel;
}

void Mouse::HandleMouseButton(const SDL_MouseButtonEvent event)
{
    //cout << "Button: " << (int)event.button << endl;
    MouseButton* button = NULL;

    if (event.button == 1)
        button = &left;
    else if (event.button == 2)
        button = &middle;
    else if (event.button == 3)
        button = &right;

    if (button != NULL)
    {
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            button->keydown = true;
            button->keypress = true;
            button->keyup = false;
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            button->keydown = false;
            button->keypress = false;
            button->keyup = true;            
        }
    }
    


}


void Mouse::ClearFrameEvents()
{
    this->xRel = 0;
    this->yRel = 0;

    right.keydown = false;
    middle.keydown = false;
    left.keydown = false;

    right.keyup = false;
    middle.keyup = false;
    left.keyup = false;
}