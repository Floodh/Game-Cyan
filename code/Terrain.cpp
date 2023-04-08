#include "Terrain.hpp"

Terrain::Terrain(Camera& camera)
    : camera{camera}, water{camera}, land{camera}
{}

void Terrain::Draw()
{
    land.Draw();
    water.Draw();
}