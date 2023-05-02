#include "Game.hpp"

//  Game logic for specific to NG1

void Game::NG1_Init()
{

    this->portal->SetPosition(0.0, 1.0, 0.0);

}

//  return true, if we completed the level
bool Game::NG1_Update()
{

    if (this->portal->IsPlayerInside())
        return true;



    return false;

}


void Game::NG1_Draw()
{

}