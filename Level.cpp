#include "Level.h"

void Level::processActions(const InputManager& actions, float time_us)
{
	if(actions.getAction(RESET) == InputManager::DOWN)
		init();

//	std::cout << actions.getAction(PLAYER_LEFT) << "\n";

#if _DEV
	//std::cout << "Movespeed:\t" << moveSpeedX*time_us << "\n";
#endif
	if (actions.getAction(PLAYER_LEFT) == InputManager::DOWN) {
		player.velocityX = -moveSpeedX;
		//player.move(Game2D::Pos2(-moveSpeedX*time_us, 0));
	} else if (actions.getAction(PLAYER_RIGHT) == InputManager::DOWN) {
		player.velocityX = +moveSpeedX;
		//player.move(Game2D::Pos2(+moveSpeedX*time_us, 0));
	} else {
		player.velocityX = 0;
	}

	if (actions.getAction(PLAYER_JUMP) == InputManager::DOWN && !player.inAir) {
		player.velocityY = moveSpeedY;
		player.inAir = true;
		//player.move(Game2D::Pos2(0, +moveSpeedY*time_us));}
	}

	if(actions.getAction(ROTATE_CLOCKWISE) == InputManager::DOWN)
		levelRotation += 90;
	if(actions.getAction(ROTATE_ANTICLOCKWISE) == InputManager::DOWN)
		levelRotation -= 90;

	if(levelRotation > 360) { levelRotation -= 360; }
	if(levelRotation <   0) { levelRotation += 360; }
}

void Level::applyGravity(float time_us) 
{
	player.velocityY -= gravity;// *time_us;
}

bool Level::checkCollision(GameObject a, GameObject b)
{
	//allign a's rect with the drawable objects
	Game2D::Rect temp = Game2D::Rect(
		a.getPos().x - (a.getRect().width/2.0f),
		a.getPos().y - (a.getRect().height / 2.0f),
		a.getRect().width ,a.getRect().height
	);

	return temp.contains(Game2D::Pos2(b.getPos().x-(b.getRect().width/2.0f), b.getPos().y-(b.getRect().height/2.0f))) ||
			temp.contains(Game2D::Pos2(b.getPos().x+(b.getRect().width/2.0f), b.getPos().y-(b.getRect().height/2.0f))) ||
			temp.contains(Game2D::Pos2(b.getPos().x-(b.getRect().width/2.0f), b.getPos().y+(b.getRect().height/2.0f))) ||
			temp.contains(Game2D::Pos2(b.getPos().x+(b.getRect().width/2.0f), b.getPos().y+(b.getRect().height/2.0f)));
}

void Level::checkPlayerCollision(float time_us)
{
	//check collision in the x direction
	player.move(Game2D::Pos2(player.velocityX * time_us, 0));

	for (const auto& wall : walls) {
		if (checkCollision(wall, player) || checkCollision(player,wall)) {
			//std::cout << "1\n";
			if (player.velocityX > 0) {
				//player is moving up so need to move them down
				//float moveDist = ((player.getPos().x - (player.getRect().width / 2.0f)) - (wall.getPos().x + (wall.getRect().width / 2.0f)));
				float moveDist = ((wall.getPos().x - (wall.getRect().width / 2.0f)) - (player.getPos().x + (player.getRect().width / 2.0f)));
				player.move(Game2D::Pos2(moveDist, 0));
				player.velocityX = 0;
			}
			else {
				float moveDist = ((wall.getPos().x + (wall.getRect().width / 2.0f)) - (player.getPos().x - (player.getRect().width / 2.0f)));
				player.move(Game2D::Pos2(moveDist, 0));
				player.velocityX = 0;
			}
		}
	}

	//check collision in the y direction
	player.move(Game2D::Pos2(0,player.velocityY * time_us));

	//check to see if the player is colliding with the wall
	for (const auto& wall : walls) {
		if (checkCollision(wall, player) || checkCollision(player,wall)) {
			//std::cout << "1\n";
			if (player.velocityY > 0) {
				//player is moving up so need to move them down
				float moveDist = ((wall.getPos().y - (wall.getRect().height / 2.0f)) - (player.getPos().y + (player.getRect().height / 2.0f)));
				player.move(Game2D::Pos2(0, moveDist));
				player.velocityY = 0;
			}
			else {
				float moveDist = ((wall.getPos().y + (wall.getRect().height / 2.0f)) - (player.getPos().y - (player.getRect().height / 2.0f)));
				player.move(Game2D::Pos2(0, moveDist));
				player.velocityY = 0;
				//player has hit the floor
				player.inAir = false;
			}
		}
	}
}

void Level::update(const InputManager& actions)
{
	endTime = Time::now();
	float elapsedTime = std::chrono::duration_cast<Microseconds>(endTime - startTime).count() / 1000000.0f;

	//std::cout << "Elapsed time\t" << elapsedTime << "\n";
	processActions(actions, elapsedTime);
	applyGravity(elapsedTime);
	
	checkPlayerCollision(elapsedTime);

	//float maxVelY = 1;
	//check to make sure the player isn't moving too fast
	if (player.velocityY > maxVelY) {
		player.velocityY = +maxVelY;
	} else if(player.velocityY < -maxVelY) {
		player.velocityY = -maxVelY;
	}
	/*if ((player->getX() + levelX) > 25)
				levelX = -(player->getX() - 25);
			else if ((player->getX() + levelX) < -25)
				levelX = -(player->getX() + 25);

			if ((player->getY() + levelY) > 25)
				levelY = -(player->getY() - 25);
			else if ((player->getY() + levelY) < -25)
				levelY = -(player->getY() + 25);*/
	if (player.getPos().x + panX > 25) {
		panX = -(player.getPos().x - 25);
	}
	else if (player.getPos().x + panX < -25) {
		panX = -(player.getPos().x + 25);
	}
	if (player.getPos().y + panY > 25) {
		panY = -(player.getPos().y - 25);
	}
	else if (player.getPos().y + panY < -25) {
		panY = -(player.getPos().y + 25);
	}

	startTime = Time::now();
}

void Level::init()
{
	//TODO
	startTime = Time::now();
	panX = panY = 0;
	levelRotation = 0;
	player.setPos(startPos);
}

void Level::draw()
{
	glPushMatrix();
		//rotate
		glTranslatef(panX, panY,0);
		for(auto it = walls.begin(); it != walls.end(); it++)
			it->draw();

		player.draw();
	glPopMatrix();
	Game2D::ScreenCoord::alignLeft();
	Game2D::Colour(1, 1, 1).draw();
	freetype::print(Game2D::Font::getFont(20), 0, 10, "Test text");
	Game2D::ScreenCoord::alignCentre();
	float temp = freetype::getLength(Game2D::Font::getFont(20), "Test text");
	Game2D::Colour(1, 1, 1).draw();
	freetype::print(Game2D::Font::getFont(20), 0 - (temp / 2.0f), 10, "Test text");
	Game2D::ScreenCoord::alignRight();
	Game2D::Colour(1, 1, 1).draw();
	freetype::print(Game2D::Font::getFont(20), 0 - temp, 10, "Test text");
	Game2D::ScreenCoord::alignCentre();
}