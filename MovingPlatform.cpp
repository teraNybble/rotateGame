#include "MovingPlatform.h"

MovingPlatform::MovingPlatform() : GameObject()
{
	setColour(Game2D::Colour(0.66f, 0.26f, 0.0f));
	startPos = getPos();
	flipped = false;
	elapsedTime_us = 0;
}

MovingPlatform::MovingPlatform(Game2D::Rect rect) : GameObject(rect)
{
	setColour(Game2D::Colour(0.66f, 0.26f, 0.0f));
	startPos = rect.pos;
	flipped = false;
	elapsedTime_us = 0;
}

void MovingPlatform::update(float time_us)
{
	elapsedTime_us += time_us;

	previousPos = getPos();

	if (elapsedTime_us > travelTime_us) { 
		setPos(endPos);
		//swap the start and end Pos so the platform goes back to the start
		Game2D::Pos2 tempPos = startPos;
		startPos = endPos;
		endPos = tempPos;
		elapsedTime_us = 0;
		flipped = !flipped;
		return;
	}

	setPos(Game2D::Pos2(
		((endPos.x - startPos.x) * (elapsedTime_us / travelTime_us)) + startPos.x,
		((endPos.y - startPos.y) * (elapsedTime_us / travelTime_us)) + startPos.y));

}

void MovingPlatform::moveOnTop(GameObject& object) {
	if (object.inAir) { return; } //object is in the air not on the platform

	Game2D::Rect moveRect = getRect();
	moveRect.width += 2;
	moveRect.height += 2;

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

	if (flipped) {
		Game2D::Pos2 tempPos = startPos;
		startPos = endPos;
		endPos = tempPos;
	}

	setPos(startPos);
	previousPos = startPos;
}