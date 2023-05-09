#include "Game.hpp"

//  Game logic for specific to NG1

void Game::NG2_Init()
{

    this->portal->SetPosition(6.5, 1.0, 6.5);
    this->player->setPosition(2.5, this->player->getPosition().y, 2.5);
    this->player->radiantAngle = 0.275;

}

//  return true, if we completed the level
bool Game::NG2_Update()
{

    if (this->portal->IsPlayerInside())
        return true;



    return false;

}


void Game::NG2_Draw()
{

}