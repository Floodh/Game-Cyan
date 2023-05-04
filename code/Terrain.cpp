#include "Terrain.hpp"

Terrain::Terrain(Camera& camera, TheSun& theSun, uint8_t* levelData, const int levelWidth, const int levelHeight, GLfloat* const backgroundColor, int& frameCount)
    : camera{camera}, theSun{theSun}, land{camera, theSun, levelData, levelWidth, levelHeight, backgroundColor}, water{camera, levelData, levelWidth, levelHeight, backgroundColor, frameCount}
{}

void Terrain::Draw()
{
    land.Draw();
    water.Draw();
}