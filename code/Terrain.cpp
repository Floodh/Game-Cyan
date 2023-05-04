#include "Terrain.hpp"

Terrain::Terrain(Camera& camera, TheSun& theSun, uint8_t* levelData, const int levelWidth, const int levelHeight, GLfloat* const backgroundColor)
    : camera{camera}, theSun{theSun}, land{camera, theSun, levelData, levelWidth, levelHeight, backgroundColor}, water{camera, levelData, levelWidth, levelHeight }
{}

void Terrain::Draw()
{
    land.Draw();
    water.Draw();
}