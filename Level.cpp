#include "Level.h"

Level::Level()
{
	exit.setRect(Game2D::Rect(0, 0, 6, 11));
	exit.setColour(Game2D::Colour::Black);
}

void Level::addSprite(Game2D::Rect rect, Game2D::Rect sprite, SpriteFlip flip)
{
	sprites.push_back(Game2D::Sprite(rect, sprite));
	sprites.back().setColour(Game2D::Colour::White);
	if (flip & 0b001) { sprites.back().flipX(); }
	if (flip & 0b010) { sprites.back().flipY(); }
	if (flip & 0b100) { sprites.back().setRot(90); }
}

void Level::processActions(const InputManager& actions, float time_us)
{
	if(actions.getAction(RESET) == InputManager::DOWN)
		init();

	if (actions.getAction(PLAYER_LEFT) == InputManager::DOWN) {
		player.velocityX = -moveSpeedX;
	} else if (actions.getAction(PLAYER_RIGHT) == InputManager::DOWN) {
		player.velocityX = +moveSpeedX;
	} else {
		player.velocityX = 0;
	}

	if (actions.getAction(PLAYER_JUMP) == InputManager::DOWN && !player.inAir) {
		player.velocityY = moveSpeedY;
		player.inAir = true;
	}

	if ((actions.getAction(ROTATE_ANTICLOCKWISE) == InputManager::DOWN) && player.getCanRotate()) {
		rotating = true;
		levelRotation += 90;
		previousPlayerRot = player.getRot();
		playerRot -= 90;
		noRotates++;
		player.setCanRotate(false);
		player.lockRotate();
	}
	if ((actions.getAction(ROTATE_CLOCKWISE) == InputManager::DOWN) && player.getCanRotate()) {
		rotating = true;
		previousPlayerRot = player.getRot();
		levelRotation -= 90;
		playerRot += 90;
		noRotates++;
		player.setCanRotate(false);
		player.lockRotate();
	}

	//if (previousPlayerRot > 360) { previousPlayerRot -= 360; }
	if(levelRotation > 360) { levelRotation -= 360; }
	if(levelRotation <   0) { levelRotation += 360; }
}

void Level::applyGravity(float time_us) 
{
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
	std::vector<GameObject> solidObjects = walls;
	solidObjects.insert(solidObjects.end(), movingPlatforms.begin(), movingPlatforms.end());

	//check collision in the y direction
	player.moveSansRot(Game2D::Pos2(0, player.velocityY * time_us), levelRotation);

	//check to see if the player is colliding with the wall
	for (const auto& wall : solidObjects) {
		if (checkCollision(wall, player) || checkCollision(player, wall)) {
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
					moveDist = ((wall.getPos().x + (wall.getRect().width / 2.0f)) - (player.getPos().x - (player.getRect().width / 2.0f)));
					break;
				case 180:
					moveDist = -((wall.getPos().y - (wall.getRect().height / 2.0f)) - (player.getPos().y + (player.getRect().height / 2.0f)));
					break;
				case 270:
					moveDist = -((wall.getPos().x - (wall.getRect().width / 2.0f)) - (player.getPos().x + (player.getRect().width / 2.0f)));
					break;
				}
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

	for (const auto& wall : solidObjects) {
		if (checkCollision(wall, player) || checkCollision(player,wall)) {
			if (player.velocityX > 0) {
				//player is moving up so need to move them down
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
				player.moveSansRot(Game2D::Pos2(moveDist, 0),levelRotation);
				player.velocityX = 0;
			}
		}
	}
}

bool Level::checkKillPlanes(float time_us)
{
	/*std::vector<Game2D::Rect> temp = killPlanes;

	for (const auto& it : movingPlatforms) {
		temp.push_back(it.getRect());
	}
	*/
	for (const auto it : killPlanes) {
		if (checkCollision(player, it) || checkCollision(it, player)) {
			return true;
		}
	}
	return false;
}

void Level::checkRotate()
{
	std::vector<GameObject> solidObjects = walls;
	solidObjects.insert(solidObjects.end(), movingPlatforms.begin(), movingPlatforms.end());

	for (const auto it : solidObjects) {
		if (checkCollision(player.getRotateBox(), it) || checkCollision(it, player.getRotateBox())) {
			player.setCanRotate(false);
			return;
		}
	}

	player.setCanRotate(true);
}

void Level::processMovingPlatforms(float time_us)
{
	for (auto& it : movingPlatforms) {
		Game2D::Rect collisionRect = it.getRect();
		switch ((int)levelRotation)
		{
			case 0:
			case 360:
				//collisionRect.height += 1;
				collisionRect.pos.y += collisionRect.height/2.0f;
				break;
			case 180:
				collisionRect.pos.y -= collisionRect.height / 2.0f;
				break;
			case 90:
				collisionRect.width += collisionRect.width / 2.0f;
				break;
			case 270:
				//TODO make it so the collision rect sticks out one above 
				collisionRect.width += collisionRect.width/2.0f;
				break;
		}
		if (!(player.inAir) && (checkCollision(player, collisionRect) || checkCollision(collisionRect, player))) {
			//std::cout << (player.inAir ? "true" : "false") << "\n";
			it.update(time_us);
			Game2D::Pos2 moveDist = it.getPos() - it.getPreviousPos();
			//std::cout << moveDist << "\n";
			//use the calculation of the collision to move the player above the floor
			player.move(moveDist);
			switch ((int)levelRotation)
			{
			case 0:
			case 360:
			case 180:
				if (std::abs(moveDist.y) > 0 && player.velocityY < 0) {
					player.velocityY = 0;
					player.inAir = false;
				}
			case 90:
			case 270:
				if (std::abs(moveDist.x) > 0 && player.velocityY < 0) {
					player.velocityY = 0;
					player.inAir = false;
				}
			default:
				break;
			}
			//player.velocityY = 0;

			//player.setCanRotate(true);
			/*float moveDist = 0;
			switch ((int)levelRotation) {
			case 360:
			case 0:
				moveDist = ((it.getPos().y + (it.getRect().height / 2.0f)) - (player.getPos().y - (player.getRect().height / 2.0f)));
				break;
			case 90:
				moveDist = ((it.getPos().x + (it.getRect().width / 2.0f)) - (player.getPos().x - (player.getRect().width / 2.0f)));
				break;
			case 180:
				moveDist = -((it.getPos().y - (it.getRect().height / 2.0f)) - (player.getPos().y + (player.getRect().height / 2.0f)));
				break;
			case 270:
				moveDist = -((it.getPos().x - (it.getRect().width / 2.0f)) - (player.getPos().x + (player.getRect().width / 2.0f)));
				break;
			}
			player.moveSansRot(Game2D::Pos2(0, moveDist), levelRotation);
			*/
			//incase of floating point errors where the player needs to be moved a number too small to be stored in a float 
			while (checkCollision(it, player) || checkCollision(player, it)) {
				player.moveSansRot(Game2D::Pos2(0, 0.001f), levelRotation);
			}
		}
		else {
			it.update(time_us);
			//if after moving the platform it collides with the player then we need to move the player
			if (checkCollision(it, player) || checkCollision(player, it)) {
				//std::cout << "push the player\n";
				Game2D::Pos2 moveDist = it.getPos() - it.getPreviousPos();
				//std::cout << moveDist << "\n";
				//use the calculation of the collision to move the player above the floor
				player.move(moveDist);
			}
			if (checkCollision(it, player) || checkCollision(player, it)) {
				std::cout << "still colliding\n";
			}
		}
	}
}

int Level::update(const InputManager& actions)
{
	endTime = Time::now();
	float elapsedTime = std::chrono::duration_cast<Microseconds>(endTime - startTime).count() / 1000000.0f;
	elapsedLevelTime += elapsedTime;
	//checkRotate();
	
	if (rotating) {
		rotateTime += elapsedTime;
		if (std::abs(levelRotation - previousRot) > 90) {
			previousRot += 360 * (levelRotation - previousRot > 0 ? 1 : -1);
		}
		drawRot = previousRot + ((levelRotation-previousRot) * (rotateTime / 1.0f));
		player.setRot(previousPlayerRot + (playerRot - previousPlayerRot) * (rotateTime / 1.0f));
		//drawRot = (levelRotation / previousRot) * rotateTime;

		if (rotateTime > 1) {
			rotateTime = 0;
			rotating = false;
			drawRot = previousRot = levelRotation;
			if (playerRot > 360) { playerRot -= 360; }
			if (playerRot < 0) { playerRot += 360; }
			player.setRot(playerRot);
			player.velocityY = 0;
			//player.inAir = true;
		}
	} else {
		processActions(actions, elapsedTime);

		
		applyGravity(elapsedTime);
		processMovingPlatforms(elapsedTime);
		checkPlayerCollision(elapsedTime);
		//processMovingPlatforms(elapsedTime);
		/*
		for (auto& it : movingPlatforms) {
			it.update(elapsedTime);
			std::cout << it.getPos() << " " << player.getPos() << "\n";
			it.moveOnTop(player);
			// move moveOnTop funtion to the level logic so the I can use the checkCollision function
		}*/

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
		}
	}

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

	checkRotate();
	startTime = Time::now();

	return 0;
}

void Level::init()
{
	startTime = Time::now();
	panX = panY = 0;
	drawRot = previousRot = levelRotation = 0;
	player.setPos(startPos);
	rotating = false;
	rotateTime = 0;
	playerRot = previousPlayerRot = 0;
	player.setRot(0);
	noRotates = 0;
	elapsedLevelTime = 0.0f;
	for (auto& it : movingPlatforms) {
		it.reset();
	}
}

void Level::draw()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, TextureManager::getTexture(3));
	glRotatef(drawRot, 0, 0, 1);
	glTranslatef(panX, panY, 0);

	exit.draw();

	for (auto it : sprites) {
		it.draw();
	}

	for (auto it = walls.begin(); it != walls.end(); it++)
		it->draw();

	for (auto it : movingPlatforms) {
		it.draw();
	}

#if _DEV
	for (auto it : killPlanes) {
		Game2D::Sprite temp(it);
		temp.setColour(Game2D::Colour(1, 0, 0, 0.5f));
		temp.draw();
	}
#endif

	player.draw();
	glPopMatrix();

	Game2D::Colour(1, 1, 1).draw();
	Game2D::ScreenCoord::alignLeft();
	freetype::print(Game2D::Font::getFont(20), 2.5, 45, "Rotates:    %d", noRotates);
	freetype::print(Game2D::Font::getFont(20), 2.5, 40, "Time:    %2.2f", elapsedLevelTime);
	Game2D::ScreenCoord::alignCentre();

	/*
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
	*/
}