#include "Level.h"

Level::Level()
{
	exit.setRect(Game2D::Rect(0, 0, 6, 11));
	exit.setColour(Game2D::Colour::Black);
}

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

	if ((actions.getAction(ROTATE_ANTICLOCKWISE) == InputManager::DOWN) && player.getCanRotate()) {
		rotating = true;
		levelRotation += 90;
		previousPlayerRot = player.getRot();
		playerRot -= 90;
		player.setCanRotate(false);
		player.lockRotate();
	}
	if ((actions.getAction(ROTATE_CLOCKWISE) == InputManager::DOWN) && player.getCanRotate()) {
		rotating = true;
		previousPlayerRot = player.getRot();
		levelRotation -= 90;
		playerRot += 90;
		player.setCanRotate(false);
		player.lockRotate();
	}

	//if (previousPlayerRot > 360) { previousPlayerRot -= 360; }
	if(levelRotation > 360) { levelRotation -= 360; }
	if(levelRotation <   0) { levelRotation += 360; }
}

void Level::applyGravity(float time_us) 
{
	//std::cout << time_us << "\n";
	player.velocityY -= gravity * time_us;// *time_us;
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

bool Level::checkCollision(Game2D::Rect a, GameObject b)
{
	//allign a's rect with the drawable objects
	Game2D::Rect temp = Game2D::Rect(
		a.pos.x - (a.width / 2.0f),
		a.pos.y - (a.height / 2.0f),
		a.width, a.height
	);

	return temp.contains(Game2D::Pos2(b.getPos().x - (b.getRect().width / 2.0f), b.getPos().y - (b.getRect().height / 2.0f))) ||
		temp.contains(Game2D::Pos2(b.getPos().x + (b.getRect().width / 2.0f), b.getPos().y - (b.getRect().height / 2.0f))) ||
		temp.contains(Game2D::Pos2(b.getPos().x - (b.getRect().width / 2.0f), b.getPos().y + (b.getRect().height / 2.0f))) ||
		temp.contains(Game2D::Pos2(b.getPos().x + (b.getRect().width / 2.0f), b.getPos().y + (b.getRect().height / 2.0f)));
}

bool Level::checkCollision(GameObject a, Game2D::Rect b)
{
	//allign a's rect with the drawable objects
	Game2D::Rect temp = Game2D::Rect(
		a.getPos().x - (a.getRect().width / 2.0f),
		a.getPos().y - (a.getRect().height / 2.0f),
		a.getRect().width, a.getRect().height
	);

	return temp.contains(Game2D::Pos2(b.pos.x - (b.width / 2.0f), b.pos.y - (b.height / 2.0f))) ||
		temp.contains(Game2D::Pos2(b.pos.x + (b.width / 2.0f), b.pos.y - (b.height / 2.0f))) ||
		temp.contains(Game2D::Pos2(b.pos.x - (b.width / 2.0f), b.pos.y + (b.height / 2.0f))) ||
		temp.contains(Game2D::Pos2(b.pos.x + (b.width / 2.0f), b.pos.y + (b.height / 2.0f)));
}


void Level::checkPlayerCollision(float time_us)
{

	//check collision in the y direction
	player.moveSansRot(Game2D::Pos2(0, player.velocityY * time_us), levelRotation);

	//check to see if the player is colliding with the wall
	for (const auto& wall : walls) {
		if (checkCollision(wall, player) || checkCollision(player, wall)) {
			//std::cout << "1\n";
			if (player.velocityY > 0) {
				//player is moving up so need to move them down
				float moveDist = 0;
				switch ((int)levelRotation) {
				case 360:
				case 0:
					moveDist = ((wall.getPos().y - (wall.getRect().height / 2.0f)) - (player.getPos().y + (player.getRect().height / 2.0f)));
					break;
				case 90:
					moveDist = ((wall.getPos().x - (wall.getRect().width / 2.0f)) - (player.getPos().x + (player.getRect().width / 2.0f)));
					break;
				case 180:
					moveDist = -((wall.getPos().y + (wall.getRect().height / 2.0f)) - (player.getPos().y - (player.getRect().height / 2.0f)));
					break;
				case 270:
					moveDist = -((wall.getPos().x + (wall.getRect().width / 2.0f)) - (player.getPos().x - (player.getRect().width / 2.0f)));
					break;
				}
				player.moveSansRot(Game2D::Pos2(0, moveDist), levelRotation);
				player.velocityY = 0;
			}
			else {
				float moveDist = 0;
				switch ((int)levelRotation) {
				case 360:
				case 0:
					moveDist = ((wall.getPos().y + (wall.getRect().height / 2.0f)) - (player.getPos().y - (player.getRect().height / 2.0f)));
					break;
				case 90:
					//std::cout << "cheacking falling at 90\n";
					moveDist = ((wall.getPos().x + (wall.getRect().width / 2.0f)) - (player.getPos().x - (player.getRect().width / 2.0f)));
					break;
				case 180:
					//std::cout << wall.getPos().y << " " << (wall.getRect().height / 2.0f) << " " << player.getPos().y << " " << (player.getRect().height / 2.0f) << "\n";
					moveDist = -((wall.getPos().y - (wall.getRect().height / 2.0f)) - (player.getPos().y + (player.getRect().height / 2.0f)));
					break;
				case 270:
					moveDist = -((wall.getPos().x - (wall.getRect().width / 2.0f)) - (player.getPos().x + (player.getRect().width / 2.0f)));
					break;
				}
				//std::cout << player.getRect() << "\n";
				//std::cout << moveDist << "\n";
				player.moveSansRot(Game2D::Pos2(0, moveDist), levelRotation);
				player.velocityY = 0;
				//player has hit the floor
				player.inAir = false;
				player.unlockRotate();
			}
		}
	}

	//check collision in the x direction
	player.moveSansRot(Game2D::Pos2(player.velocityX * time_us, 0),levelRotation);

	for (const auto& wall : walls) {
		if (checkCollision(wall, player) || checkCollision(player,wall)) {
			//std::cout << "1\n";
			if (player.velocityX > 0) {
				//player is moving up so need to move them down
				//float moveDist = ((player.getPos().x - (player.getRect().width / 2.0f)) - (wall.getPos().x + (wall.getRect().width / 2.0f)));
				float moveDist = 0;
				switch ((int)levelRotation)
				{
				case 360:
				case 0:
					moveDist = ((wall.getPos().x - (wall.getRect().width / 2.0f)) - (player.getPos().x + (player.getRect().width / 2.0f)));
					break;
				case 90:
					moveDist = -((wall.getPos().y + (wall.getRect().height / 2.0f)) - (player.getPos().y - (player.getRect().height / 2.0f)));
					break;
				case 180:
					moveDist = -((wall.getPos().x + (wall.getRect().width / 2.0f)) - (player.getPos().x - (player.getRect().width / 2.0f)));
					break;
				case 270:
					moveDist = ((wall.getPos().y - (wall.getRect().height / 2.0f)) - (player.getPos().y + (player.getRect().height / 2.0f)));
					break;
				}
				player.moveSansRot(Game2D::Pos2(moveDist, 0),levelRotation);
				player.velocityX = 0;
			}
			else if(player.velocityX < 0){
				float moveDist = 0;
				switch ((int)levelRotation)
				{
				case 360:
				case 0:
					moveDist = ((wall.getPos().x + (wall.getRect().width / 2.0f)) - (player.getPos().x - (player.getRect().width / 2.0f)));
					break;
				case 90:
					moveDist = -((wall.getPos().y - (wall.getRect().height / 2.0f)) - (player.getPos().y + (player.getRect().height / 2.0f)));
					break;
				case 180:
					moveDist = -((wall.getPos().x - (wall.getRect().width / 2.0f)) - (player.getPos().x + (player.getRect().width / 2.0f)));
					break;
				case 270:
					moveDist = ((wall.getPos().y + (wall.getRect().height / 2.0f)) - (player.getPos().y - (player.getRect().height / 2.0f)));
					break;
				}
				//float moveDist = ((wall.getPos().x + (wall.getRect().width / 2.0f)) - (player.getPos().x - (player.getRect().width / 2.0f)));
				player.moveSansRot(Game2D::Pos2(moveDist, 0),levelRotation);
				player.velocityX = 0;
			}
		}
	}

}

bool Level::checkKillPlanes(float time_us)
{
	for (const auto it : killPlanes) {
		if (checkCollision(player, it) || checkCollision(it, player)) {
			return true;
		}
	}
	return false;
}

void Level::checkRotate()
{
	for (const auto it : walls) {
		if (checkCollision(player.getRotateBox(), it) || checkCollision(it, player.getRotateBox())) {
			player.setCanRotate(false);
			return;
		}
	}

	player.setCanRotate(true);
}

int Level::update(const InputManager& actions)
{
	endTime = Time::now();
	float elapsedTime = std::chrono::duration_cast<Microseconds>(endTime - startTime).count() / 1000000.0f;
	checkRotate();
	//std::cout << "Elapsed time\t" << elapsedTime << "\n";
	if (rotating) {
		rotateTime += elapsedTime;
		if (std::abs(levelRotation - previousRot) > 90) {
			previousRot += 360 * (levelRotation - previousRot > 0 ? 1 : -1);
		}
		drawRot = previousRot + ((levelRotation-previousRot) * (rotateTime / 1.0f));
		player.setRot(previousPlayerRot + (playerRot - previousPlayerRot) * (rotateTime / 1.0f));
		//drawRot = (levelRotation / previousRot) * rotateTime;
		//std::cout << drawRot << " = " << levelRotation << " * " << rotateTime << "/1" << "\n";

		if (rotateTime > 1) {
			rotateTime = 0;
			rotating = false;
			drawRot = previousRot = levelRotation;
			if (playerRot > 360) { playerRot -= 360; }
			if (playerRot < 0) { playerRot += 360; }
			player.setRot(playerRot);
			player.velocityY = 0;
			//player.inAir = true;
			//std::cout << "Done rotating to " << levelRotation << "\n";
		}
	} else {
		processActions(actions, elapsedTime);
		applyGravity(elapsedTime);

		checkPlayerCollision(elapsedTime);

		//check to see if the player has walked off an edge
		if (player.velocityY < 0) {
			//if they have set them to be in air
			player.inAir = true;
		}

		if (checkKillPlanes(elapsedTime)) {
			init();
		}
		if (exit.isInside(player.getRect())) {
			std::cout << "Level Done!\n";
			return 1;
			//std::cout << "Level Done!\n";
		}
	}

	//float maxVelY = 1;
	//check to make sure the player isn't moving too fast
	if (player.velocityY > maxVelY) {
		player.velocityY = +maxVelY;
	} else if(player.velocityY < -maxVelY) {
		player.velocityY = -maxVelY;
	}
	
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

	return 0;
}

void Level::init()
{
	//TODO
	startTime = Time::now();
	panX = panY = 0;
	drawRot = previousRot = levelRotation = 0;
	player.setPos(startPos);
	rotating = false;
	rotateTime = 0;
	playerRot = previousPlayerRot = 0;
	player.setRot(0);
}

void Level::draw()
{
	glPushMatrix();
		glRotatef(drawRot, 0, 0, 1);
		glTranslatef(panX, panY,0);
		
		exit.draw();

		for(auto it = walls.begin(); it != walls.end(); it++)
			it->draw();

		player.draw();
	glPopMatrix();
	
	//std::cout << levelRotation << "\n";

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