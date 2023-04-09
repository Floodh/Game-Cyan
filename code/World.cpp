#include "World.hpp"

World::World()
    :
        drawObjects{std::vector<IDrawObject*>()},
        camera{},
        theSun{},
        terrain{this->camera, this->theSun}
{

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