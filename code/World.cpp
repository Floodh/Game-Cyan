#include "World.hpp"

#include "Console.hpp"

World::World(uint8_t* levelData, int levelWidth, int levelHeight)
    :
        drawObjects{std::vector<IDrawObject*>()},
        camera{},
        theSun{},
        terrain{this->camera, this->theSun, levelData, levelWidth, levelHeight}
{
    Console::WriteLine("The Sun:");
    Console::WriteLine(this->theSun.direction, 3);
    Console::WriteLine(this->theSun.color, 3);

}

void World::Draw()
{

    camera.UpdateViewMatrix();
    
    for (IDrawObject* drawObject : this->drawObjects)
        drawObject->Draw();

    this->terrain.Draw();

}

void World::Update()
{

    //  here be game logic

}