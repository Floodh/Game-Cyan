#include "Terrain.hpp"

Terrain::Terrain(Camera& camera, TheSun& theSun, uint8_t* levelData, int levelWidth, int levelHeight)
    : camera{camera}, theSun{theSun}, water{camera, levelData, levelWidth, levelHeight }, land{camera, theSun, levelData, levelWidth, levelHeight }
{}

void Terrain::Draw()
{
    land.Draw();
    water.Draw();
}