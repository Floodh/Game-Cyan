#pragma once

#include "SDL.h"
#include "GL_utilities.h"

#include "IDrawObject.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Camera.hpp"
#include "World.hpp"
#include "LoadBMP.hpp"
#include "MainMenu.hpp"

#include "Player.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <iomanip> // for setw

namespace GameState
{
enum GameState 
{
    Quit,
    Loading,
    MainMenu,
    Playing
};
}

//  master class, here everything is ultimetly managed
//  is divided into Update, Draw and HandleEvent
class Game
{

    public:
        Game(int windowWidth, int windowHeight); //  move code from main that initilizes the graphic here
        ~Game();
        void NewGame(int level);

        void Update();  //  may change its state
        void Draw();
        //  this function only needs to pass through the event to Keyboard
        void HandleEvent(const SDL_Event& event);

        GameState::GameState gameState;


    private:

        //  
        int windowWidth, windowHeight;
        SDL_Window * window = nullptr;
        SDL_GLContext glContext = nullptr;
        Keyboard keyboard;
        Mouse mouse;

        uint8_t* levelData = nullptr;
        MainMenu* mainMenu = nullptr;
        World* world = nullptr;


        Player* player;

        

};