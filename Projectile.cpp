#include "Projectile.h"

Projectile::Projectile() : GameObject(Game2D::Rect(0, 0, 1, 1)) 
{
	Projectile(Game2D::Pos2(0, 0));
}

Projectile::Projectile(Game2D::Pos2 pos) : GameObject(Game2D::Rect(pos,1,1))
{
	speed = 10;
	setSprite(Game2D::Sprite(Game2D::Rect(pos,1,1), Game2D::Rect(0.934f, 0.035f, 0.56f, 0.035f)));
	setColour(Game2D::Colour::White);
	//setTexture(Rect(0.934f, 0.035f, 0.56f, 0.035f));
}

void Projectile::setDirection(Game2D::Pos2 direction) 
{ 
	//normalise the direction vector
	float c = sqrtf((direction.x * direction.x) + (direction.y * direction.y));
	//movX = x / c;
	//movY = y / c;
	this->direction = Game2D::Pos2(direction.x/c,direction.y/c);
}

void Projectile::update(float time)
{
	//std::cout << "moved from " << getPos();
	move(Game2D::Pos2(direction.x * time * speed, direction.y * time * speed));
	//std::cout << " to " << getPos() << "\n";
}