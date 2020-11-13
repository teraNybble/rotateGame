#ifndef ENEMY_H
#define ENEMY_H

#include "MovingPlatform.h"

class Enemy : public MovingPlatform
{
private:
	Game2D::Rect headBox;
	Game2D::Pos2 headBoxOffset;
public:
	enum Direction { NONE, NORTH, EAST, SOUTH, WEST };
	Enemy();
	Enemy(Game2D::Pos2 pos);

	inline Game2D::Rect getHeadBox() const { return headBox; }

	inline void setHead(Direction dir) {
		headBox = Game2D::Rect(0, 0, 5, 2.5f);
		switch (dir)
		{
		case Enemy::NONE:
			headBox = Game2D::Rect(0, 0, 0, 0);
			break;
		case Enemy::NORTH:
			headBoxOffset = Game2D::Pos2(0, +1.25f);
			break;
		case Enemy::EAST:
			headBoxOffset = Game2D::Pos2(+1.25f, 0);
			break;
		case Enemy::SOUTH:
			headBoxOffset = Game2D::Pos2(0, -1.25f);
			break;
		case Enemy::WEST:
			headBoxOffset = Game2D::Pos2(+1.25f, 0);
			break;
		}
	}

	inline void update(float time_us) {
		MovingPlatform::update(time_us);
		headBox.pos = getPos() + headBoxOffset;
	}

#if _DEV
	inline void draw() {
		MovingPlatform::draw();
		Game2D::Sprite temp(headBox);
		temp.setColour(Game2D::Colour(0, 1, 1, 0.5f));
		temp.draw();
	}
#endif
};

#endif // !ENEMY_H