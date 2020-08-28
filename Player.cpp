#include "Player.h"

Player::Player() : GameObject(Game2D::Rect(0,0,5,10))
{
	hitBox = Game2D::Rect(0, 0, 5, 10);
	rotateBox = Game2D::Rect(0, 0, 10, 10);
	//setRect(Game2D::Rect(0,0,5,10));
	setColour(Game2D::Colour::Cyan);
}


void Player::setRot(float rot)
{
	GameObject::setRot(rot);
	if (rot < 0) { rot += 360; }
	if (rot > 360) { rot -= 360; }
	//std::cout << "Setting player Rot " << rot << "\n";
	switch (int(rot)) {
	case 360:
	case 0:
	case 180:
		//GameObject::getPos
		hitBox = (Game2D::Rect(getPos(), 5, 10));
		break;
	case 90:
	case 270:
		hitBox = (Game2D::Rect(getPos(), 10, 5));
		break;
	}
}

void Player::moveSansRot(Game2D::Pos2 pos, float rot) {
	switch ((int)rot) {
	case 360:
	case 0:
		move(pos);
		break;
	case 90:
		move(Game2D::Pos2(pos.y, -pos.x));
		break;
	case 180:
		move(Game2D::Pos2(-pos.x, -pos.y));
		break;
	case 270:
		move(Game2D::Pos2(-pos.y, pos.x));
		break;
	}
}