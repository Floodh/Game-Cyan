#include "Game.hpp"

//  Game logic for specific to NG1

void Game::NG1_Init()
{

    this->portal->SetPosition(5.5, 1.0, 2.5);
    this->player->setPosition(1.5, this->player->getPosition().y, 8.5);
    this->player->radiantAngle = 2.3;

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