//  these needs to be included in this order,
//  openGl is not allowed to be included before GL_utilities
#include "SDL.h"
#include "GL_utilities.h"

#include "Game.hpp"

#include <string>
#include <iostream>


#include "Terrain.hpp"

int main(int argc, char *argv[])
{


    SDL_Event event = { 0 };
    bool should_quit = false;

    // TRY-CATCH TO FACILITATE COMMON CLEAN-UP CODE
    try {

        Game game{600,600};
        game.NewGame(0);


        // GAME LOOP:
        while (!should_quit) {
            // EVENT LOOP:
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                    should_quit = true;
                    break;
                default:
                    //  call Keyboard.HandleEvent here!!!!!!!!
                    game.HandleEvent(event);
                    // switch (event.key.keysym.sym) {
                    // case SDLK_ESCAPE:
                    //     should_quit = true;
                    //     break;
                    // }
                    break;
                }
            }

            // Clear the screen to WHITE:
            glClearColor(0.f, 0.f, 0.2f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


            //  swap buffers
            game.Draw();
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