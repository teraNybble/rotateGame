#include "Enemy.h"

Enemy::Enemy() : MovingPlatform(Game2D::Rect(0, 0, 5, 5)) 
{
	Enemy(Game2D::Pos2(0, 0));
	//headBox = Game2D::Rect(0, 1.25f, 5, 2.5f);
}

Enemy::Enemy(Game2D::Pos2 pos) : MovingPlatform(Game2D::Rect(pos, 5, 5))
{
	//headBoxOffset = Game2D::Pos2(0, 1.25f);
	headBox = Game2D::Rect(pos+headBoxOffset, 5, 2.5f);
	setColour(Game2D::Colour(1, 0, 0));
}