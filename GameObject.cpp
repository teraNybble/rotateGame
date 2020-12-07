#include "GameObject.h"

GameObject::GameObject()
{
	//rect = Game2D::Rect(0,0,10,10);
	sprite = Game2D::Sprite(Game2D::Rect(0,0,10,10));
	hitBox = Game2D::Rect(0, 0, 10, 10);
	inAir = false;
}

GameObject::GameObject(Game2D::Rect rect)
{
	//this->rect = rect;
	sprite = Game2D::Sprite(rect);
	hitBox = rect;
	inAir = false;
}

bool GameObject::isInside(Game2D::Rect rect) {
	Game2D::Rect tempBox = Game2D::Rect(hitBox.pos.x - hitBox.width / 2.0f, hitBox.pos.y - hitBox.height / 2.0f, hitBox.width, hitBox.height);

	/*std::cout << tempBox.contains(Game2D::Pos2(rect.pos.x - (rect.width / 2.0f), rect.pos.y - (rect.height / 2.0f))) <<
		tempBox.contains(Game2D::Pos2(rect.pos.x - (rect.width / 2.0f), rect.pos.y + (rect.height / 2.0f))) <<
		tempBox.contains(Game2D::Pos2(rect.pos.x + (rect.width / 2.0f), rect.pos.y + (rect.height / 2.0f))) <<
		tempBox.contains(Game2D::Pos2(rect.pos.x + (rect.width / 2.0f), rect.pos.y - (rect.height / 2.0f))) << "\n";*/


	return tempBox.contains(Game2D::Pos2(rect.pos.x - (rect.width / 2.0f), rect.pos.y - (rect.height / 2.0f))) &&
		tempBox.contains(Game2D::Pos2(rect.pos.x - (rect.width / 2.0f), rect.pos.y + (rect.height / 2.0f))) &&
		tempBox.contains(Game2D::Pos2(rect.pos.x + (rect.width / 2.0f), rect.pos.y + (rect.height / 2.0f))) &&
		tempBox.contains(Game2D::Pos2(rect.pos.x + (rect.width / 2.0f), rect.pos.y - (rect.height / 2.0f)));
}

void GameObject::moveSansRot(Game2D::Pos2 pos, float rot) {
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

void GameObject::draw() const
{
	//std::cout << hitBox << "\n" << sprite.getRect() << "\n\n";
	//colour.draw();
	try {
		sprite.draw();
	} catch (std::exception e) {
		std::cerr << "[ERROR] " << e.what() << std::endl;
	}
}