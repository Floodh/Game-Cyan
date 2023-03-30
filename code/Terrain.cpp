#include "Terrain.hpp"

Terrain::Terrain(Camera& camera)
    : camera{camera}, water{camera}
{}

void Terrain::Draw()
{
    water.Draw();
}