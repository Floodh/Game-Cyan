#include "Game.hpp"

#define NUMOFCOLLECTABLES 12


//  Game logic for specific to NG1

void Game::NG4_Init()
{

    this->portal->SetPosition(109.0, 1.0, 106.0);
    this->player->setPosition(3.0, this->player->getPosition().y, 3.0);
    this->player->radiantAngle = 0.1;

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
    this->numberOfCollectables = NUMOFCOLLECTABLES;

    this->collectables = new Collectable[NUMOFCOLLECTABLES]
    {
        Collectable(5.5f, 1.0f, 2.5f, *this->player, this->camera, green, this->backgroundColor),   //  #1
        Collectable(7.5f, 1.0f, 2.5f, *this->player, this->camera, green, this->backgroundColor),   //  #2
        
        Collectable(5.5f, 1.0f, 3.5f, *this->player, this->camera, blue, this->backgroundColor),   //  #sp1

        Collectable(8.5f, 1.0f, 4.5f, *this->player, this->camera, green, this->backgroundColor),   //  #3
        Collectable(9.5f, 1.0f, 6.5f, *this->player, this->camera, green, this->backgroundColor),   //  #4
        Collectable(7.5f, 1.0f, 8.5f, *this->player, this->camera, green, this->backgroundColor),   //  #5
        Collectable(3.5f, 1.0f, 7.5f, *this->player, this->camera, green, this->backgroundColor),   //  #6

        Collectable(2.5f, 1.0f, 5.5f, *this->player, this->camera, blue, this->backgroundColor),   //  #sp2

        Collectable(1.5f, 1.0f, 6.5f, *this->player, this->camera, green, this->backgroundColor),   //  #7
        Collectable(2.5f, 1.0f, 4.5f, *this->player, this->camera, green, this->backgroundColor),   //  #8
        Collectable(3.5f, 1.0f, 8.5f, *this->player, this->camera, green, this->backgroundColor),   //  #9
        Collectable(4.5f, 1.0f, 2.5f, *this->player, this->camera, green, this->backgroundColor)    //  #10

    };


    for (int i = 0; i < NUMOFCOLLECTABLES; i++)
    {
        collectables[i].canBeCollected = true;
        collectables[i].isCollected = false;
    }

    collectedCount = 0;
    showPortal = false;

}

//  return true, if we completed the level
bool Game::NG4_Update()
{

    if (collectedCount == NUMOFCOLLECTABLES)
    if (this->portal->IsPlayerInside())
    {
        this->playerOther->mostRecentPkg = NULL;
        return true;
    }

    for (int i = 0; i < NUMOFCOLLECTABLES; i++)
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

    

    if (this->playerOther->mostRecentPkg != NULL)
    {
        int collectedData = this->playerOther->mostRecentPkg[8];

        if (this->playerOther->mostRecentPkg[3] == this->currentLevel)
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
        }
    }

    if (collectedCount >= NUMOFCOLLECTABLES)
        showPortal = true; 

    return false;


}


void Game::NG4_Draw()
{
    for (int i = 0; i < NUMOFCOLLECTABLES; i++)
    {
        if (collectables[i].canBeCollected == true)
        if (collectables[i].isCollected == false)
        {
            collectables[i].Draw();
        }
    }
}