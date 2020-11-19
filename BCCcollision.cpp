#include "BCCcollision.h"

std::vector<BCCcollision> BCCcollision::rectToBC(Game2D::Rect r) const
{
	std::vector<BCCcollision> temp;
	temp.push_back(BCCcollision(Game2D::Pos2(r.pos.x - (r.width / 2.0f), r.pos.y - (r.height / 2.0f)), Game2D::Pos2(r.pos.x - (r.width / 2.0f), r.pos.y - (r.height / 2.0f)), 0));
	temp.push_back(BCCcollision(Game2D::Pos2(r.pos.x - (r.width / 2.0f), r.pos.y + (r.height / 2.0f)), Game2D::Pos2(r.pos.x - (r.width / 2.0f), r.pos.y + (r.height / 2.0f)), 0));
	temp.push_back(BCCcollision(Game2D::Pos2(r.pos.x + (r.width / 2.0f), r.pos.y - (r.height / 2.0f)), Game2D::Pos2(r.pos.x + (r.width / 2.0f), r.pos.y - (r.height / 2.0f)), 0));
	temp.push_back(BCCcollision(Game2D::Pos2(r.pos.x + (r.width / 2.0f), r.pos.y + (r.height / 2.0f)), Game2D::Pos2(r.pos.x + (r.width / 2.0f), r.pos.y + (r.height / 2.0f)), 0));
	//temp.push_back(BCCcollision(r.pos.x, r.pos.x, r.pos.y, r.pos.y, 0));
	//temp.push_back(BCCcollision(r.pos.x, r.pos.x, r.pos.y + r.height, r.pos.y + r.height, 0));
	//temp.push_back(BCCcollision(r.pos.x, c.getMaxX(), c.getMaxY(), c.getMaxY(), 0));
	//temp.push_back(BCCcollision(r.pos.x, c.getMaxX(), c.getMinY(), c.getMinY(), 0));

	return temp;
}

BCCcollision::BCCcollision()
{
	minPos = maxPos = Game2D::Pos2(0, 0);
	radius = 0;
}

BCCcollision::BCCcollision(Game2D::Pos2 min, Game2D::Pos2 max, float r) 
{
	maxPos = max;
	minPos = min;
	radius = r;
}

void BCCcollision::setPoints(Game2D::Pos2 min, Game2D::Pos2 max, float r)
{
	maxPos = max;
	minPos = min;
	radius = r;
}

bool BCCcollision::isColliding(Game2D::Rect r) const
{
	std::vector<BCCcollision> temp = rectToBC(r);
//	for (std::vector<BCCollision>::iterator it = temp.begin(); it != temp.end(); it++)
	for (const auto& it : temp) {
		if (isColliding(it)) {
			return true;
		}
	}

	return false;
}

bool BCCcollision::isColliding(BCCcollision c) const
{
	if ((((getCentre(minPos.x, maxPos.x) - getCentre(c.minPos.x, c.maxPos.x)) *
		(getCentre(minPos.x, maxPos.x) - getCentre(c.minPos.x, c.maxPos.x))) +
		((getCentre(minPos.y, maxPos.y) - getCentre(c.minPos.y, c.maxPos.y)) *
		(getCentre(minPos.y, maxPos.y) - getCentre(c.minPos.y, c.maxPos.y)))) <
			((radius + c.radius) * (radius + c.radius)))
	{
		return true;
	}

	return false;
}

void BCCcollision::draw() const
{
#if _DEV
	//glColor4f(0.0f, 1.0f, 1.0f, 0.7f);
	drawColour.draw();
	glBegin(GL_POLYGON);
	for (float i = 0; i < 360; i += 5)
	{
		float xcoord = getCentre(minPos.x, maxPos.x) + radius * cosf(i * (PI / 180.0f));
		float ycoord = getCentre(minPos.y, maxPos.y) + radius * sinf(i * (PI / 180.0f));
		glVertex2f(xcoord, ycoord);
	}
	glEnd();
#endif
}