#include "GameObject.h"

GameObject::GameObject()
{
	//rect = Game2D::Rect(0,0,10,10);
	sprite = Game2D::Sprite(Game2D::Rect(0,0,10,10));
	inAir = false;
}

GameObject::GameObject(Game2D::Rect rect)
{
	//this->rect = rect;
	sprite = Game2D::Sprite(rect);
	inAir = false;
}

void GameObject::draw()
{
	//colour.draw();
	sprite.draw();
}