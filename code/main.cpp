//  these needs to be included in this order,
//  openGl is not allowed to be included before GL_utilities
#include "SDL.h"
#include "GL_utilities.h"

#include "Game.hpp"

#include <string>
#include <iostream>


#include "Terrain.hpp"
#include "LoadBMP.hpp"
#include "Console.hpp"


int main(int argc, char *argv[])
{

    int width = 10, height = 10, channels = 0;
    uint8_t* levelFile = LoadBMP("data/level/Level1Map.bmp", width, height, channels);
    std::cout << "Loading level " << width << ","  << height << "," << channels << std::endl;

    if (levelFile == NULL)
        throw std::runtime_error("Couldn't load level");

    Console::WriteLine(levelFile, width, height, 4);


    SDL_Event event = { 0 };
    bool should_quit = false;

    //
    try {

        Game game{600,600};
        game.NewGame(0);


        // GAME LOOP:
        while (!should_quit) {

            // EVENT LOOP:
            while (SDL_PollEvent(&event)) 
            {
                switch (event.type) 
                {
                    case SDL_QUIT:
                        should_quit = true;
                        break;
                    default:
                        game.HandleEvent(event);
                        break;
                }
            }

            game.Update();

            // Clear the screen
            glClearColor(0.f, 0.f, 0.2f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //  swap buffers
            game.Draw();

            _sleep(24);
        }
    }
    catch (std::string e) {
        std::cout << e << std::endl;;
    }
    catch (...) {
        std::cout << "Unknown exception caught!" << std::endl;
    }


    SDL_Quit();
    return 0;
}