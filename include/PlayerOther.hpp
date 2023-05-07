#pragma once

#include "Player.hpp"
#ifdef _WIN32
    #include "P2P.hpp"
#endif

class PlayerOther : public Player
{

    public:

        PlayerOther(Camera& camera, uint8_t* levelData, int width, int height);

        void Update();

        void AddConnection();


};

