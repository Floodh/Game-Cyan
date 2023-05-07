#pragma once

#include "Player.hpp"
#include "Client.hpp"

class PlayerOther : public Player
{

    public:

        PlayerOther(Camera& camera, uint8_t* levelData, int width, int height);

        void Update();

        void AddConnection();


};

