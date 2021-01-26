#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

class Boss : public Enemy
{
private:
	//attacks
	void bulletsX(Game2D::Pos2 playerPos);
	void bulletsY(Game2D::Pos2 playerPos);
	void summonSwooper(Game2D::Pos2 playerPos);
	void summonShooter(Game2D::Pos2 shooterPos);
	//!attacks
public:
	Boss();
	Boss(Game2D::Pos2 pos);
};


#endif //BOSS_H
