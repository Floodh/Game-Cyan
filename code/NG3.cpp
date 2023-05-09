#include "Game.hpp"

#include <iostream>

using namespace std;

//  Game logic for specific to NG1

#define NUMOFCOLLECTABLES 9

GLfloat* green = new GLfloat[3]{0.0f, 1.0f, 2.0f};
int collectedCount;

void Game::NG3_Init()
{

    this->portal->SetPosition(8.5, 1.0, 6.5);
    this->player->setPosition(7.5, this->player->getPosition().y, 4.5);
    this->player->radiantAngle = 3.4;

    this->numberOfCollectables = NUMOFCOLLECTABLES;
    if (this->collectables == NULL)
        this->collectables = new Collectable[NUMOFCOLLECTABLES]
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
    else
    {
        this->collectables[0].canBeCollected = true;
        this->collectables[0].isCollected = false;
        this->collectables[1].canBeCollected = true;
        this->collectables[1].isCollected = false;
        this->collectables[2].canBeCollected = true;
        this->collectables[2].isCollected = false;
        this->collectables[3].canBeCollected = true;
        this->collectables[3].isCollected = false;
        this->collectables[4].canBeCollected = true;
        this->collectables[4].isCollected = false;
        this->collectables[5].canBeCollected = true;
        this->collectables[5].isCollected = false;
        this->collectables[6].canBeCollected = true;
        this->collectables[6].isCollected = false;
        this->collectables[7].canBeCollected = true;
        this->collectables[7].isCollected = false;
        this->collectables[8].canBeCollected = true;
        this->collectables[8].isCollected = false;
    }


    for (int i = 0; i < NUMOFCOLLECTABLES; i++)
    {
        collectables[i].canBeCollected = true;
        collectables[i].isCollected = false;
    }

    collectedCount = 0;
    showPortal = false;


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


    int collectedData = 0;
    if (this->playerOther->mostRecentPkg != NULL)
        collectedData = this->playerOther->mostRecentPkg[8];

    cout << "Collectables data: " << collectedData << endl;
    for (int i = this->numberOfCollectables - 1; i > -1 ; i--)
    {
        int isTaken = collectedData & 0b1;
        if (isTaken == true)
        {
            if (collectables[i].canBeCollected == true)
            if (collectables[i].isCollected == false)
            {
                collectables[i].canBeCollected = false;
                collectables[i].isCollected = true;
                collectedCount++;
            }
        }
        collectedData = collectedData >> 1;
        cout << isTaken << ", ";
    }
    //cout << endl;

    if (collectedCount >= 9)
        showPortal = true; 

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