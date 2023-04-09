#include "Terrain.hpp"

Terrain::Terrain(Camera& camera, TheSun& theSun)
    : camera{camera}, theSun{theSun}, water{camera}, land{camera, theSun}
{}

void Terrain::Draw()
{
    land.Draw();
    water.Draw();
}