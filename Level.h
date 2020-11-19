#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
//#include <map>
#include <chrono>
//#include <vector>
#include "InputManager.h"
#include "Fonts.h"
#include "ScreenCoord.h"
#include "MovingPlatform.h"
#include "TextureManager.h"
#include "Enemy.h"

using Time = std::chrono::steady_clock;
using Microseconds = std::chrono::microseconds;
using Clock = std::chrono::steady_clock::time_point;

class Level
{
private:
	const float moveSpeedX = 50;
	const float moveSpeedY = 160;
	const float gravity = 450;
	const float maxVelY = 200;
	const float maxVelX = 1;
	Player player;
	GameObject exit;
	std::vector<GameObject> walls;
	std::vector<Game2D::Rect> killPlanes;
	std::vector<MovingPlatform> movingPlatforms;
	std::vector<Game2D::Sprite> sprites;
	std::vector<std::pair<Enemy, bool>> enemies;
	std::vector<Game2D::Sprite> noRotateZones;

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

	int noRotates;
	float elapsedLevelTime;

	void processActions(const InputManager& actions, float time_us);
	void applyGravity(float time_us);
	bool checkCollision(GameObject a, GameObject b);
	bool checkCollision(Game2D::Rect a, GameObject b);
	bool checkCollision(GameObject a, Game2D::Rect b);
	bool checkCollision(Game2D::Rect a, Game2D::Rect b);
	void checkPlayerCollision(float time_us);
	bool checkKillPlanes(float time_us);
	void checkRotate();
	void processMovingPlatforms(float time_us);
	bool processEnemies(float time_us);
	bool enemyAligned(Enemy::Direction dir);
public:
	enum SpriteFlip { NONE = 0b00, X = 0b01, Y = 0b10, BOTH = 0b11, ROT = 0b100, ROTX = 0b101, ROTY = 0b110, ROTXY = 0b111 };
	Level();
	//level creation
	inline void setStartPos(Game2D::Pos2 pos) { startPos = pos; }
	inline void setExitPos(Game2D::Pos2 pos) { exit.setPos(pos); }
	inline void setExitRext(Game2D::Rect rect) { exit.setRect(rect); }
	inline void addWall(Game2D::Rect wall) { walls.push_back(GameObject(wall)); walls.back().setColour(Game2D::Colour::Green); }
	inline void addKillPlane(Game2D::Rect plane) { killPlanes.push_back(plane); }
	inline void addMovingPlatform(MovingPlatform platform) { movingPlatforms.push_back(platform); }
	inline void addEnemy(Enemy enemy) { enemies.push_back(std::pair<Enemy, bool>(enemy, true)); }
	inline void addNoRotateZone(Game2D::Rect rect) { noRotateZones.push_back(Game2D::Sprite(rect)); noRotateZones.back().setColour(Game2D::Colour(1, 0, 0, 0.25f)); }
	void addSprite(Game2D::Rect rect, Game2D::Rect sprite, SpriteFlip flip = SpriteFlip::NONE);
	//end level creation

	void init();

	enum LevelActions { PLAYER_LEFT, PLAYER_RIGHT, PLAYER_JUMP, RESET, ROTATE_CLOCKWISE, ROTATE_ANTICLOCKWISE};

	int update(const InputManager& actions);

	void draw();
};


#endif //LEVEL_H