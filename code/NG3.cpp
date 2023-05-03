#include "Game.hpp"

//  Game logic for specific to NG1

void Game::NG3_Init()
{

    this->portal->SetPosition(8.5, 1.0, 6.5);
    this->player->setPosition(7.5, 0.75, 4.5);

    //  8.5, 1.5
    //  4.5, 2.5
    //  3.5, 2.5
    //  1.5, 8.5
    //  3.5, 6.5
    //  2.5, 5.5
    //  1.5, 6.5
    //  2.5, 7.5
    //  5.5, 8.5

}

//  return true, if we completed the level
bool Game::NG3_Update()
{

    if (this->portal->IsPlayerInside())
        return true;



    return false;

}


void Game::NG3_Draw()
{

}