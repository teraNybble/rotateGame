#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H

#include "GameObject.h"
#include <vector>

class MovingPlatform : public GameObject
{
private:
	//might change to be a vector of poses to allow non streigt line paths
	Game2D::Pos2 startPos;
	Game2D::Pos2 endPos;
	float travelTime_us;
	float elapsedTime_us;
	bool flipped;
	//used to see how far the platform has moved so we can move the player on top
	Game2D::Pos2 previousPos;

	std::vector<std::pair<Game2D::Pos2, float>> path;
	int pathPos;
public:
	MovingPlatform();
	MovingPlatform(Game2D::Rect rect, Game2D::Pos2 endPos, float travelTime);

	//inline void setEndPos(Game2D::Pos2 pos) { endPos = pos; }
	//inline void setTravelTime(float time_us) { travelTime_us = time_us; }
	inline void setPath(std::vector<std::pair<Game2D::Pos2, float>> path) { this->path = path; }

	/*
	inline void updateTime(float time) { elapsedTime_us += time; }
	inline float& getTime() { return elapsedTime_us; }
	*/

	void reset();

	void update(float time_us);
	void moveOnTop(GameObject& object);
	inline Game2D::Pos2 getPreviousPos() { return previousPos; }

	//inline void draw() { std::cout << elapsedTime_us << "\n"; GameObject::draw(); }
};

#endif // !MOVINGPLATFORM_H