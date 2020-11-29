#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"
#include <Pos2.h>
#include <math.h>

class Projectile : public GameObject
{
private:
	Game2D::Pos2 direction;
	float speed;
public:
	Projectile();
	Projectile(Game2D::Pos2 pos);

	void setDirection(Game2D::Pos2 direction);
	void update(float time);
};

#endif // !PROJECTILE_H