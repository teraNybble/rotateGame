#ifndef ENEMY_H
#define ENEMY_H

#include "MovingPlatform.h"
#include "BCCcollision.h"

class Enemy : public MovingPlatform
{
public:
	enum Direction { NONE, NORTH, EAST, SOUTH, WEST };
	enum Type { STILL, MOVING, SWOOPING, ROTATING, SHOOTING, BOSS };
private:
	Direction headDirection;
	Game2D::Rect headBox;
	Game2D::Pos2 headBoxOffset;
	BCCcollision attackRadius;
	std::vector<std::pair<Game2D::Pos2, float>> originalPath;
	bool swooping;
	bool playerInRadius;
	bool canRotate;
	float recharge;
	float attackSpeed;
	Type type;
	Game2D::Sprite feetSprite;
public:
	static Game2D::Colour enemyColour;
	static Game2D::Colour feetColour;

	Enemy();
	Enemy(Game2D::Pos2 pos, Game2D::Pos2 endPos, float time,Type type);

	inline Game2D::Rect getHeadBox() const { return headBox; }
	inline void setAttackRadius(float r) { attackRadius.setRadius(r); }
	inline void setAttackSpeed(float s) { attackSpeed = s; }

	void setHead(Direction dir);
	inline Enemy::Direction getHead() const { return headDirection; }
	inline Type getType() const { return type; }

	void update(float time_us);
	bool isInRadius(Game2D::Rect r);

	inline void reset() {
		swooping = false;
		setPath(originalPath);
		MovingPlatform::reset();
	}

	inline void draw()
	{
		MovingPlatform::draw();
		feetSprite.draw();
#if _DEV
		if (Debug::getDrawHitboxes()) {
			Game2D::Sprite temp(headBox);
			temp.setColour(Game2D::Colour(0, 1, 1, 0.5f));
			temp.draw();
			attackRadius.draw();
		}
#endif
	}

#if _DEV
	inline void setRadiusColour(Game2D::Colour c) { attackRadius.setColour(c); }
	/*
	inline void draw() {
		MovingPlatform::draw();
		if (Debug::getDrawHitboxes()) {
			Game2D::Sprite temp(headBox);
			temp.setColour(Game2D::Colour(0, 1, 1, 0.5f));
			temp.draw();
			attackRadius.draw();
		}
	}*/
#endif
};

#endif // !ENEMY_H