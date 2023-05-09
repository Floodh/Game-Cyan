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
#include "Portal.hpp"
#include "Collectable.hpp"
#include "PlayerOther.hpp"
#include "Client.hpp"

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

        void UpdateMessage();

        //  
        int windowWidth, windowHeight;
        int frameCount = 0;
        SDL_Window * window = nullptr;
        SDL_GLContext glContext = nullptr;

        Keyboard keyboard;
        Mouse mouse;

        int currentLevel = 0;
        uint8_t* levelData = nullptr;
        MainMenu* mainMenu = nullptr;
        World* world = nullptr;
        Camera camera;


        Player* player = nullptr;
        Portal* portal = nullptr;
        PlayerOther* playerOther = nullptr;

        GLfloat* const backgroundColor = new GLfloat[3]{0.5f, 0.5f, 0.8f};

        bool showPortal = true;

    //  NewGames

        int const totalLevels = 4;
        Collectable* collectables = NULL;
        int numberOfCollectables = 0;

        void NG1_Init();
        bool NG1_Update();
        void NG1_Draw();

        void NG2_Init();
        bool NG2_Update();
        void NG2_Draw();

        void NG3_Init();
        bool NG3_Update(); 
        void NG3_Draw();

        void NG4_Init();
        bool NG4_Update();
        void NG4_Draw();
};