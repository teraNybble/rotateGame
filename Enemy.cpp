#include "Enemy.h"

Enemy::Enemy() : MovingPlatform(Game2D::Rect(0, 0, 5.1, 5.1),Game2D::Pos2(0,0),0) 
{
	Enemy(Game2D::Pos2(0, 0),Game2D::Pos2(0, 0),0, STILL);
	//headBox = Game2D::Rect(0, 1.25f, 5, 2.5f);
}

Enemy::Enemy(Game2D::Pos2 pos, Game2D::Pos2 endPos, float time, Type type) : MovingPlatform(Game2D::Rect(pos, 5.1, 5.1),endPos,time)
{
	//headBoxOffset = Game2D::Pos2(0, 1.25f);
	headBox = Game2D::Rect(pos+headBoxOffset, 5.1, 2.6f);
	headDirection = NORTH;
	setSprite(Game2D::Sprite(Game2D::Rect(0, 0, 5.1, 5.1), Game2D::Rect(0, 0.599609375, 0.1015625, 0.099609375)));
	setColour(Game2D::Colour(1, 0, 0));
	attackRadius.setPoints(pos, pos, 0);
	originalPath.push_back(std::pair<Game2D::Pos2,float>(pos, time));
	originalPath.push_back(std::pair<Game2D::Pos2, float>(endPos, time));
	swooping = false;
	attackSpeed = 1.0f;
	this->type = type;
	canRotate = true;
}

void Enemy::update(float time_us) {
	if (MovingPlatform::update(time_us) && swooping && (type == SWOOPING)) {
		swooping = false;
		setPath(originalPath);
		MovingPlatform::reset();
	}
	headBox.pos = getPos() + headBoxOffset;
	switch (type)
	{
	case Enemy::STILL:
		break;
	case Enemy::MOVING:
		break;
	case Enemy::SWOOPING:
		break;	
	case Enemy::SHOOTING:
	case Enemy::ROTATING:
		if (!canRotate) {
			recharge += time_us;
			if (recharge > attackSpeed) {
				canRotate = true;
				recharge = 0;
			}
		}
		break;
	case Enemy::BOSS:
		break;
	default:
		break;
	}
}

bool Enemy::isInRadius(Game2D::Rect r)
{
	switch (type)
	{
	case Enemy::STILL:
		break;
	case Enemy::MOVING:
		break;
	case Enemy::SWOOPING:
		if (attackRadius.isColliding(r)) {
			if (!swooping) {
				swooping = true;

				float radius = attackRadius.getRadius();
				int attackDirection = (getPos().x < r.pos.x ? -1 : +1);
				int swoopDirection = (getPos().y < r.pos.y ? -1 : 1);

				std::vector<std::pair<Game2D::Pos2, float>> swoopPath;
				swoopPath.clear();
				/*
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(Game2D::Pos2(getPos().x, getPos().y), 0000.0f));
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(Game2D::Pos2(getPos().x, (getPos().y - (swoopDirection * radius * 0.56f))), 0.5f * attackSpeed));
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(Game2D::Pos2(getPos().x, (getPos().y - (swoopDirection * radius * 0.56f))), 0.75f));
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(Game2D::Pos2(getPos().x - (attackDirection * radius * 1.1f), (getPos().y - (swoopDirection * radius * 0.56f))), 0.5f * attackSpeed));
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(Game2D::Pos2(getPos().x - (attackDirection * radius * 1.1f), getPos().y), 2.0f));
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(originalPath.at(0).first, 2.0f));
				*/

				swoopPath.push_back(std::pair<Game2D::Pos2, float>(Game2D::Pos2(getPos().x, getPos().y), 0000.0f));
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(Game2D::Pos2(getPos().x, r.pos.y), 0.5f * attackSpeed));
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(Game2D::Pos2(getPos().x, r.pos.y), 0.75f));
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(Game2D::Pos2(r.pos.x - (5 * attackDirection),r.pos.y), 0.5f * attackSpeed));
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(Game2D::Pos2(r.pos.x - (5 * attackDirection), getPos().y), 2.0f));
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(originalPath.at(0).first, 2.0f));

/*				std::cout << Game2D::Pos2(getPos().x, getPos().y) << "\t" << 0000.0f << "\n";
				std::cout << Game2D::Pos2(getPos().x, (getPos().y - (swoopDirection * radius * 0.56f))) << "\t" << 0.5f * attackSpeed << "\n";
				std::cout << Game2D::Pos2(getPos().x, (getPos().y - (swoopDirection * radius * 0.56f))) << "\t" << 0.5f << "\n";
				std::cout << Game2D::Pos2(getPos().x - (attackDirection * radius * 1.1f), (getPos().y - (swoopDirection * radius * 0.56f))) << "\t" << 0.5f * attackSpeed << "\n";
				std::cout << Game2D::Pos2(getPos().x - (attackDirection * radius * 1.1f), getPos().y) << "\t" << 2.0f << "\n";
				std::cout << originalPath.at(0).first << "\t" << 2.0f << "\n\n";
				*/

				setPath(swoopPath);

				return true;
			}
		}
		break;
	case Enemy::SHOOTING:
	case Enemy::ROTATING:
		if (attackRadius.isColliding(r) && canRotate) {
			canRotate = false;
			return true;
		}
		return false;
		break;
	case Enemy::BOSS:
		break;
	default:
		break;
	}

	

	return false;
}