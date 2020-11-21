#ifndef BCCCOLLISION_H
#define BCCCOLLISION_H

#include <vector>
#include <Rect.h>
#if _DEV
#include "glew.h"
#include <Colour.h>
#define PI 3.141592653589793238462643383279
#endif

class BCCcollision
{
private:
	Game2D::Pos2 minPos;
	Game2D::Pos2 maxPos;
	float radius;
#if _DEV
	Game2D::Colour drawColour;
#endif

	inline float getCentre(float min, float max) const { return ((max - min) / 2.0f) + min; }
	std::vector<BCCcollision> rectToBC(Game2D::Rect r) const;
public:
	BCCcollision();
	BCCcollision(Game2D::Pos2 start, Game2D::Pos2 end, float r);

	void setPoints(Game2D::Pos2 start, Game2D::Pos2 end, float r);
	inline void setRadius(float r) { radius = r; }
	inline float getRadius() const { return radius; }

	inline void move(Game2D::Pos2 p) { minPos += p; maxPos += p; }

#if _DEV
	inline void setColour(Game2D::Colour c) { drawColour = c; }
#endif

	bool isColliding(Game2D::Rect r) const;
	bool isColliding(BCCcollision c) const;

	void draw() const;
};


#endif // !BCCCOLLISION_H