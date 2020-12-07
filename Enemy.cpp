#include "Enemy.h"

Game2D::Colour Enemy::enemyColour = Game2D::Colour(0.62, 0.165, 0.165);
Game2D::Colour Enemy::feetColour = Game2D::Colour(0.4, 0.255, 0.157);

Enemy::Enemy() : MovingPlatform(Game2D::Rect(0, 0, 5.1, 5.1),Game2D::Pos2(0,0),0,0) 
{
	Enemy(Game2D::Pos2(0, 0),Game2D::Pos2(0, 0),0, STILL);
	//headBox = Game2D::Rect(0, 1.25f, 5, 2.5f);
}

Enemy::Enemy(Game2D::Pos2 pos, Game2D::Pos2 endPos, float time, Type type) : MovingPlatform(Game2D::Rect(pos, 5.1, 5.1),endPos,time,0)
{
	//headBoxOffset = Game2D::Pos2(0, 1.25f);
	//enemyColour = Game2D::Colour(0.62, 0.165, 0.165);
	//feetColour = Game2D::Colour(0.4, 0.255, 0.157);
	headBox = Game2D::Rect(pos+headBoxOffset, 5.1, 2.6f);
	headDirection = NORTH;
	setSprite(Game2D::Sprite(Game2D::Rect(0, 0, 5.1, 5.1), Game2D::Rect(0, 0.599609375, 0.1015625, 0.099609375)));
	//setColour(Game2D::Colour(1, 0, 0));
	setColour(enemyColour);
	attackRadius.setPoints(pos, pos, 0);
	originalPath.push_back(std::pair<Game2D::Pos2,float>(pos, time));
	originalPath.push_back(std::pair<Game2D::Pos2, float>(endPos, time));
	swooping = false;
	attackSpeed = 1.0f;
	this->type = type;
	canRotate = true;
	/*
	switch (headDirection)
	{
	case Enemy::NONE:
		feetSprite = Game2D::Sprite(Game2D::Rect(0, 0, 0, 0), Game2D::Rect(0, 0, 0, 0));
		break;
	case Enemy::NORTH:
		feetSprite = Game2D::Sprite(Game2D::Rect(pos, 5.1, 5.1), Game2D::Rect(0.1015625, 0.599609375, 0.1015625, 0.099609375));
		break;
	case Enemy::EAST:
		feetSprite = Game2D::Sprite(Game2D::Rect(pos, 5.1, 5.1), Game2D::Rect(0.1015625, 0.599609375, 0.1015625, 0.099609375));
		feetSprite.setRot(90);
		break;
	case Enemy::SOUTH:
		feetSprite = Game2D::Sprite(Game2D::Rect(pos, 5.1, 5.1), Game2D::Rect(0.1015625, 0.599609375, 0.1015625, 0.099609375));
		feetSprite.setRot(180);
		break;
	case Enemy::WEST:
		feetSprite = Game2D::Sprite(Game2D::Rect(pos, 5.1, 5.1), Game2D::Rect(0.1015625, 0.599609375, 0.1015625, 0.099609375));
		feetSprite.setRot(270);
		break;
	default:
		break;
	}
	feetSprite.setColour(Game2D::Colour::White);
	*/
}

void Enemy::setHead(Direction dir) {
	headDirection = dir;
	headBox = Game2D::Rect(0, 0, 5.1, 2.6f);
	switch (dir)
	{
	case Enemy::NONE:
		headBox = Game2D::Rect(0, 0, 0, 0);
		feetSprite = Game2D::Sprite(Game2D::Rect(0, 0, 0, 0), Game2D::Rect(0, 0, 0, 0));
		break;
	case Enemy::NORTH:
		headBoxOffset = Game2D::Pos2(0, +1.25f);
		feetSprite = Game2D::Sprite(Game2D::Rect(0, 0, 5.1, 5.1), Game2D::Rect(0.1015625, 0.599609375, 0.1015625, 0.099609375));
		break;
	case Enemy::EAST:
		headBox = Game2D::Rect(0, 0, 2.5f, 5);
		headBoxOffset = Game2D::Pos2(+1.25f, 0);
		feetSprite = Game2D::Sprite(Game2D::Rect(0, 0, 5.1, 5.1), Game2D::Rect(0.1015625, 0.599609375, 0.1015625, 0.099609375));
		feetSprite.setRot(270);
		break;
	case Enemy::SOUTH:
		headBoxOffset = Game2D::Pos2(0, -1.25f);
		feetSprite = Game2D::Sprite(Game2D::Rect(0, 0, 5.1, 5.1), Game2D::Rect(0.1015625, 0.599609375, 0.1015625, 0.099609375));
		feetSprite.setRot(180);
		break;
	case Enemy::WEST:
		headBox = Game2D::Rect(0, 0, 2.5f, 5);
		headBoxOffset = Game2D::Pos2(-1.25f, 0);
		feetSprite = Game2D::Sprite(Game2D::Rect(0, 0, 5.1, 5.1), Game2D::Rect(0.1015625, 0.599609375, 0.1015625, 0.099609375));
		feetSprite.setRot(90);
		break;
	}
	feetSprite.setColour(feetColour);
}

void Enemy::update(float time_us) {
	if (MovingPlatform::update(time_us) && swooping && (type == SWOOPING)) {
		swooping = false;
		setPath(originalPath);
		MovingPlatform::reset();
	}
	headBox.pos = getPos() + headBoxOffset;
	attackRadius.setPoints(getPos(), getPos(), attackRadius.getRadius());
	feetSprite.setPos(getPos());
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