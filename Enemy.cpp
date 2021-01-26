#include "Enemy.h"

Game2D::Colour Enemy::enemyColour = Game2D::Colour(0.62, 0.165, 0.165);
Game2D::Colour Enemy::feetColour = Game2D::Colour(0.4, 0.255, 0.157);
Game2D::Colour Enemy::eyeColour = Game2D::Colour::White;
Game2D::Colour Enemy::angryEyeColour = Game2D::Colour(0.745, 0.475, 0.29);

Enemy::Enemy() : MovingPlatform(Game2D::Rect(0, 0, 5.1, 5.1),Game2D::Pos2(0,0),0,0) 
{
	Enemy(Game2D::Pos2(0, 0),Game2D::Pos2(0, 0),0, STILL);
}

Enemy::Enemy(Game2D::Pos2 pos, Game2D::Pos2 endPos, float time, Type type) : MovingPlatform(Game2D::Rect(pos, 5.1, 5.1),endPos,time,0)
{
	headBox = Game2D::Rect(pos+headBoxOffset, 5.1, 2.6f);
	headDirection = NORTH;
	setSprite(Game2D::Sprite(getRect(), Game2D::Rect(0, 0.5, 0.19921875, 0.19921875)));
	setColour(enemyColour);
	attackRadius.setPoints(pos, pos, 0);
	angerRadius.setPoints(pos, pos, 0);
	originalPath.push_back(std::pair<Game2D::Pos2,float>(pos, time));
	originalPath.push_back(std::pair<Game2D::Pos2, float>(endPos, time));
	swooping = false;
	attackSpeed = 1.0f;
	this->type = type;
	canRotate = true;
	recharge = attackSpeed;
}

void Enemy::setHead(Direction dir) {
	headDirection = dir;
	headBox = Game2D::Rect(0, 0, 5.1, 2.6f);
	eyeSprite = Game2D::Sprite(getRect(), Game2D::Rect(0.3984375, 0.5, 0.19921875, 0.19921875));
	feetSprite = Game2D::Sprite(getRect(),Game2D::Rect(0.19921875, 0.5, 0.19921875, 0.19921875));
	switch (dir)
	{
	case Enemy::NONE:
		headBox = Game2D::Rect(0, 0, 0, 0);
		feetSprite = Game2D::Sprite(Game2D::Rect(0, 0, 0, 0), Game2D::Rect(0, 0, 0, 0));
		break;
	case Enemy::NORTH:
		headBoxOffset = Game2D::Pos2(0, +1.25f);
		break;
	case Enemy::EAST:
		headBox = Game2D::Rect(0, 0, 2.5f, 5);
		headBoxOffset = Game2D::Pos2(+1.25f, 0);
		feetSprite.setRot(270);
		eyeSprite.setRot(270);
		break;
	case Enemy::SOUTH:
		headBoxOffset = Game2D::Pos2(0, -1.25f);
		feetSprite.setRot(180);
		eyeSprite.setRot(180);
		break;
	case Enemy::WEST:
		headBox = Game2D::Rect(0, 0, 2.5f, 5);
		headBoxOffset = Game2D::Pos2(-1.25f, 0);
		feetSprite.setRot(90);
		eyeSprite.setRot(90);
		break;
	}
	feetSprite.setColour(feetColour);
	eyeSprite.setColour(eyeColour);
}

bool Enemy::update(float time_us) {
	if (MovingPlatform::update(time_us) && swooping && (type == SWOOPING)) {
		swooping = false;
		setPath(originalPath);
		MovingPlatform::reset();
	}
	headBox.pos = getPos() + headBoxOffset;
	attackRadius.setPoints(getPos(), getPos(), attackRadius.getRadius());
	angerRadius.setPoints(getPos(), getPos(), angerRadius.getRadius());
	feetSprite.setPos(getPos());
	eyeSprite.setPos(getPos());
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

	return false;
}

bool Enemy::isInRadius(Game2D::Rect r)
{
	if(attackRadius.isColliding(r)){
		eyeSprite.setColour(angryEyeColour);
	} else {
		eyeSprite.setColour(eyeColour);
	}

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

				swoopPath.push_back(std::pair<Game2D::Pos2, float>(Game2D::Pos2(getPos().x, getPos().y), 0000.0f));
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(Game2D::Pos2(getPos().x, r.pos.y), 0.5f * attackSpeed));
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(Game2D::Pos2(getPos().x, r.pos.y), 0.75f));
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(Game2D::Pos2(r.pos.x - (5 * attackDirection),r.pos.y), 0.5f * attackSpeed));
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(Game2D::Pos2(r.pos.x - (5 * attackDirection), getPos().y), 2.0f));
				swoopPath.push_back(std::pair<Game2D::Pos2, float>(originalPath.at(0).first, 2.0f));

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

void Enemy::isInAngerRange(Game2D::Rect r)
{
	if (!canRotate && (recharge/attackSpeed < 0.75f)) {
		eyeSprite.setTextureCoords(Game2D::Rect(0.80078125, 0.5, 0.19921875, 0.19921875));
	} else if(angerRadius.isColliding(r)){
		eyeSprite.setTextureCoords(Game2D::Rect(0.59765625, 0.5, 0.19921875, 0.19921875));
	} else {
		eyeSprite.setTextureCoords(Game2D::Rect(0.3984375, 0.5, 0.19921875, 0.19921875));
	}
}
