#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
//#include <map>
#include <chrono>
//#include <vector>
#include "InputManager.h"
#include "Fonts.h"
#include "ScreenCoord.h"

using Time = std::chrono::steady_clock;
using Microseconds = std::chrono::microseconds;
using Clock = std::chrono::steady_clock::time_point;

class Level
{
private:
	const float moveSpeedX = 50;
	const float moveSpeedY = 120;
	const float gravity = 300;
	const float maxVelY = 200;
	const float maxVelX = 1;
	Player player;
	GameObject exit;
	std::vector<GameObject> walls;
	std::vector<Game2D::Rect> killPlanes;

	Game2D::Pos2 startPos;

	//timers
	Clock startTime;
	Clock endTime;
	//end timers

	float panX, panY;
	float levelRotation, previousRot, drawRot;
	float playerRot, previousPlayerRot;
	bool rotating;
	float rotateTime;

	void processActions(const InputManager& actions, float time_us);
	void applyGravity(float time_us);
	bool checkCollision(GameObject a, GameObject b);
	bool checkCollision(Game2D::Rect a, GameObject b);
	bool checkCollision(GameObject a, Game2D::Rect b);
	void checkPlayerCollision(float time_us);
	bool checkKillPlanes(float time_us);
	void checkRotate();
public:
	Level();
	//level creation
	inline void setStartPos(Game2D::Pos2 pos) { startPos = pos; }
	inline void setExitPos(Game2D::Pos2 pos) { exit.setPos(pos); }
	inline void setExitRext(Game2D::Rect rect) { exit.setRect(rect); }
	inline void addWall(Game2D::Rect wall) { walls.push_back(GameObject(wall)); walls.back().setColour(Game2D::Colour::Green); }
	inline void addKillPlane(Game2D::Rect plane) { killPlanes.push_back(plane); }
	//end level creation

	void init();

	enum LevelActions { PLAYER_LEFT, PLAYER_RIGHT, PLAYER_JUMP, RESET, ROTATE_CLOCKWISE, ROTATE_ANTICLOCKWISE};

	int update(const InputManager& actions);

	void draw();
};


#endif //LEVEL_H