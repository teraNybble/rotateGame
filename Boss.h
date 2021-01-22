#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

class Boss : public Enemy
{
private:
public:
	Boss();
	Boss(Game2D::Pos2 pos);
};


#endif //BOSS_H
