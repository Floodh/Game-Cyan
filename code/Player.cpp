#include "Player.hpp"


Player::Player(Camera& camera)
: camera{camera}, HP{100}, Points{0}
{
    this->position = new GLfloat[3]{0.0f, 0.0f, 0.0f};

}

Player::~Player()
{}


void Player::Update()
{
    ;
}


void Player::Draw()
{
    ;
}

void Player::setPosition(const GLfloat x, const GLfloat y, const GLfloat z)
{
    this->position[0] = x;
    this->position[1] = y; // We may not want to change the y-value here
    this->position[2] = z;
}