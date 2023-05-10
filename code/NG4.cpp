#include "Game.hpp"

#define NUMOFCOLLECTABLES 12


//  Game logic for specific to NG1

void Game::NG4_Init()
{

    this->portal->SetPosition(109.0, 1.0, 106.0);
    this->player->setPosition(3.0, this->player->getPosition().y, 3.0);
    this->player->radiantAngle = 0.1;


}

//  return true, if we completed the level
bool Game::NG4_Update()
{

     if (this->portal->IsPlayerInside())
        return true;



    return false;



}


void Game::NG4_Draw()
{

}