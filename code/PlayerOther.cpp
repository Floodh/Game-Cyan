#include "PlayerOther.hpp"


using namespace std;

//  special update function to handle the player position
//  being determined by input from connection

PlayerOther::PlayerOther(Camera& camera, uint8_t* levelData, int width, int height, GLfloat x, GLfloat y, GLfloat z, GLfloat* backgroundColor)
    : Player(camera, levelData, width, height, x, y, z, backgroundColor)
{}

void PlayerOther::Update()
{
#ifdef _WIN32
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

        int level = data[3];
        GLfloat x = *((GLfloat*)(&data[4]));
        GLfloat z = *((GLfloat*)(&data[5]));
        GLfloat y = *((GLfloat*)(&data[6]));
        GLfloat rotation = *((GLfloat*)(&data[7]));

        this->loadedLevel = level;
        this->setPosition(x, y, z);
        this->radiantAngle = rotation;
        rotationMatrix[0] =	cos(this->radiantAngle / 1.0);
        rotationMatrix[2] = sin(this->radiantAngle / 1.0);
        rotationMatrix[8] = -sin(this->radiantAngle / 1.0);
        rotationMatrix[10] = cos(this->radiantAngle / 1.0);
    }   

#endif
}



void PlayerOther::AddConnection()
{

}