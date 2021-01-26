#include "MovingPlatform.h"

Game2D::Colour MovingPlatform::platformColour = Game2D::Colour(0.49, 0.31, 0.19);

MovingPlatform::MovingPlatform() : GameObject()
{
	MovingPlatform(Game2D::Rect(0, 0, 0, 0),Game2D::Pos2(0,0),0.0f,0.0f);
}

MovingPlatform::MovingPlatform(Game2D::Rect rect, Game2D::Pos2 endPos, float travelTime, float pauseTime) : GameObject(rect)
{
	setColour(platformColour);
	startPos = rect.pos;
	this->endPos = endPos;
	flipped = false;
	elapsedTime_us = 0;
	pathPos = 0;
	path.push_back(std::pair<Game2D::Pos2, float>(rect.pos, travelTime));
	path.push_back(std::pair<Game2D::Pos2, float>(rect.pos, pauseTime));
	path.push_back(std::pair<Game2D::Pos2, float>(endPos, travelTime));
	path.push_back(std::pair<Game2D::Pos2, float>(endPos, pauseTime));
}

void MovingPlatform::setPath(std::vector<std::pair<Game2D::Pos2, float>> path)
{
	this->path = path; 
	elapsedTime_us = 0; 
	pathPos = 0;
	endPos = path[pathPos].first;
	travelTime_us = path[pathPos].second;
}

bool MovingPlatform::update(float time_us)
{
	bool returnVal = false;
	elapsedTime_us += time_us;

	previousPos = getPos();

	if (elapsedTime_us >= travelTime_us) {
		elapsedTime_us = elapsedTime_us - travelTime_us;
		if (++pathPos < path.size()) {
			startPos = path[pathPos - 1].first;
			endPos = path[pathPos].first;
			travelTime_us = path[pathPos].second;
		} else {
			pathPos = 0;
			startPos = path[path.size() - 1].first;
			endPos = path[pathPos].first;
			travelTime_us = path[pathPos].second;
			returnVal = true;
		}
	}

	setPos(Game2D::Pos2(
		((endPos.x - startPos.x) * (elapsedTime_us / travelTime_us)) + startPos.x,
		((endPos.y - startPos.y) * (elapsedTime_us / travelTime_us)) + startPos.y));

	return returnVal;
}

void MovingPlatform::moveOnTop(GameObject& object) {
	if (object.inAir) { return; } //object is in the air not on the platform

	Game2D::Rect moveRect = getRect();
	moveRect.width += 0.5;
	moveRect.height += 0.5;

	if(moveRect.contains(Game2D::Pos2(object.getPos().x,object.getPos().y)) 
		|| moveRect.contains(Game2D::Pos2(object.getPos().x, object.getPos().y + object.getRect().height))
		|| moveRect.contains(Game2D::Pos2(object.getPos().x + object.getRect().width, object.getPos().y))
		|| moveRect.contains(Game2D::Pos2(object.getPos().x + object.getRect().width, object.getPos().y + object.getRect().height))) {
		object.move(getPos() - previousPos);
	}
}

void MovingPlatform::reset()
{
	elapsedTime_us = 0;

	pathPos = 0;

	pathPos = 0;
	startPos = path[path.size() - 1].first;
	endPos = path[pathPos].first;
	travelTime_us = path[pathPos].second;

	setPos(startPos);
	previousPos = startPos;
}