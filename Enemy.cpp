#include "Enemy.h"

Enemy::Enemy() : MovingPlatform(Game2D::Rect(0, 0, 5, 5),Game2D::Pos2(0,0),0) 
{
	Enemy(Game2D::Pos2(0, 0),Game2D::Pos2(0, 0),0);
	//headBox = Game2D::Rect(0, 1.25f, 5, 2.5f);
}

Enemy::Enemy(Game2D::Pos2 pos, Game2D::Pos2 endPos, float time) : MovingPlatform(Game2D::Rect(pos, 5, 5),endPos,time)
{
	//headBoxOffset = Game2D::Pos2(0, 1.25f);
	headBox = Game2D::Rect(pos+headBoxOffset, 5, 2.5f);
	headDirection = NORTH;
	setColour(Game2D::Colour(1, 0, 0));
	attackRadius.setPoints(pos, pos, 0);
}

bool Enemy::isInRadius(Game2D::Rect r)
{
	return attackRadius.isColliding(r);
}