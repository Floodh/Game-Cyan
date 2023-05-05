#include "Game.hpp"

#include <iostream>

using namespace std;

//  Game logic for specific to NG1


Collectable* collectables = NULL;
GLfloat* green = new GLfloat[3]{0.0f, 1.0f, 2.0f};
int collectedCount;

void Game::NG3_Init()
{

    this->portal->SetPosition(8.5, 1.0, 6.5);
    this->player->setPosition(7.5, this->player->getPosition().y, 4.5);


    if (collectables == NULL)
        collectables = new Collectable[9]
        {
            Collectable(8.5f, 1.0f, 1.5f, *this->player, this->camera, green, this->backgroundColor),
            Collectable(4.5f, 1.0f, 2.5f, *this->player, this->camera, green, this->backgroundColor),
            Collectable(3.5f, 1.0f, 2.5f, *this->player, this->camera, green, this->backgroundColor),
            Collectable(1.5f, 1.0f, 8.5f, *this->player, this->camera, green, this->backgroundColor),

            Collectable(3.5f, 1.0f, 6.5f, *this->player, this->camera, green, this->backgroundColor),
            Collectable(2.5f, 1.0f, 5.5f, *this->player, this->camera, green, this->backgroundColor),
            Collectable(1.5f, 1.0f, 6.5f, *this->player, this->camera, green, this->backgroundColor),
            Collectable(2.5f, 1.0f, 7.5f, *this->player, this->camera, green, this->backgroundColor),

            Collectable(5.5f, 1.0f, 8.5f, *this->player, this->camera, green, this->backgroundColor)
        };

    for (int i = 0; i < 9; i++)
    {
        collectables[i].canBeCollected = true;
        collectables[i].isCollected = false;
    }

    collectedCount = 0;


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

    if (collectedCount == 9)
    if (this->portal->IsPlayerInside())
        return true;

    for (int i = 0; i < 9; i++)
    {
        if (collectables[i].canBeCollected == true)
        if (collectables[i].isCollected == false)
        if (collectables[i].IsPlayerInside())
        {
            collectables[i].canBeCollected = false;
            collectables[i].isCollected = true;
            collectedCount++;
        }
    }

    return false;

}


void Game::NG3_Draw()
{
    for (int i = 0; i < 9; i++)
    {
        if (collectables[i].canBeCollected == true)
        if (collectables[i].isCollected == false)
        {
            collectables[i].Draw();
        }
    }
}