#include "Player.h"

Player::Player() : GameObject(Game2D::Rect(0,0,5,10))
{
	//setRect(Game2D::Rect(0,0,5,10));
	setColour(Game2D::Colour::Cyan);
}