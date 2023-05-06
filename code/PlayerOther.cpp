#include "PlayerOther.hpp"


using namespace std;

//  special update function to handle the player position
//  being determined by input from connection

PlayerOther::PlayerOther(Camera& camera, uint8_t* levelData, int width, int height)
    : Player(camera, levelData, width, height)
{

}

void PlayerOther::Update()
{
    Message event{NULL};
    while(eventQueue.Consume(event)) 
    {
        // Process the event
        cout << endl << "Event message: {" << event.message << "}" << endl;

        int* data = (int*)event.message;
        cout << "Answer = '" << data[0] << "," << data[1] << "\n";

        cout << "status =  " << data[2] << ", level loaded = " << data[3] << endl;
        for (int i = 4; i < PKGSIZE / 8;)
        {
            cout << "i = " << i << ", " << data[i++] << "," << data[i++] << "," << data[i++] << endl;
        }

        GLfloat x = *((GLfloat*)(&data[4]));
        GLfloat z = *((GLfloat*)(&data[5]));

        this->setPosition(x, this->getPosition().y, z);


    }   



}


void PlayerOther::AddConnection()
{

}