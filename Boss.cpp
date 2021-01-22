#include "Boss.h"

Boss::Boss()
{
	Boss(Game2D::Pos2(0,0));
}

Boss::Boss(Game2D::Pos2 pos) : Enemy(pos,pos,0,Enemy::BOSS)
{
	setRect(Game2D::Rect(pos,35,35));
	//enemyColour = Game2D::Colour::Magenta;
	//setColour(enemyColour);
	//set
}