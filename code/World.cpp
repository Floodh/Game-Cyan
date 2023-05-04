#include "World.hpp"

#include "Console.hpp"

World::World(uint8_t* levelData, const int levelWidth, const int levelHeight, Mouse& mouse, Camera& camera, GLfloat* const backgroundColor, int& frameCount)
    :
        drawObjects{std::vector<IDrawObject*>()},
        camera{camera},
        theSun{},
        terrain{this->camera, this->theSun, levelData, levelWidth, levelHeight, backgroundColor, frameCount}
{
    Console::WriteLine("The Sun:");
    Console::WriteLine(this->theSun.direction, 3);
    Console::WriteLine(this->theSun.color, 3);

}

void World::Draw()
{

    for (IDrawObject* drawObject : this->drawObjects)
        drawObject->Draw();

    this->terrain.Draw();

}

void World::Update()
{

    //  here be game logic

}