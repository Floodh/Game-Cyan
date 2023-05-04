#include "Game.hpp"

//  Game logic for specific to NG1

void Game::NG4_Init()
{

    this->portal->SetPosition(5.5, 1.0, 6.5);
    this->player->setPosition(5.5, this->player->getPosition().y, 1.5);


    //  5.5, 2.5    #1
    //  7.5, 2.5    #2
    //  5.5, 3.5    #special 1
    //  8.5, 4.5    #3
    //  9.5, 6.5    #4
    //  7.5, 8.5    #5
    //  should take special 1
    //  3.5, 7.5    #6
    //  2.5, 5.5    #special 2
    //  1.5, 6.5    #7
    //  2.5, 4.5    #8
    //  3.5, 8.5    #9
    //  should take special 2
    //  4.5, 2.5    #10


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