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
	for (int i = 0; i < 7; i++) {
		if (lockedKeys[i]) {
			lockedKeys[i] = (actions.getAction(i) == InputManager::DOWN);
		}
	}

	if(actions.getAction(RESET) == InputManager::DOWN)
		init();

	if (!lockedKeys[PLAYER_LEFT] && actions.getAction(PLAYER_LEFT) == InputManager::DOWN) {
		player.velocityX = -moveSpeedX;
	} else if (!lockedKeys[PLAYER_RIGHT] && actions.getAction(PLAYER_RIGHT) == InputManager::DOWN) {
		player.velocityX = +moveSpeedX;
	} else {
		player.velocityX = 0;
	}

	if (!lockedKeys[PLAYER_JUMP] && actions.getAction(PLAYER_JUMP) == InputManager::DOWN && !player.inAir) {
		player.velocityY = moveSpeedY;
		player.inAir = true;
	}


	if (!lockedKeys[ROTATE_ANTICLOCKWISE] && (actions.getAction(ROTATE_ANTICLOCKWISE) == InputManager::DOWN) && player.getCanRotate()) {
		rotating = true;
		levelRotation += 90;
		previousPlayerRot = player.getRot();
		playerRot -= 90;
		noRotates++;
		player.setCanRotate(false);
		player.lockRotate();
	}
	if (!lockedKeys[ROTATE_CLOCKWISE] && (actions.getAction(ROTATE_CLOCKWISE) == InputManager::DOWN) && player.getCanRotate()) {
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

bool Level::checkCollision(Game2D::Rect a, Game2D::Rect b)
{
	Game2D::Rect temp = Game2D::Rect(
		a.pos.x - (a.width / 2.0f),
		a.pos.y - (a.height / 2.0f),
		a.width, a.height
	); 

	//Game2D::Rect temp = a;

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
	for (const auto& it : noRotateZones) {
		if (checkCollision(it.getRect(), player)) {
			player.setCanRotate(false);
			return;
		}
	}

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
collisionRect.width += collisionRect.width / 2.0f;
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

bool Level::processEnemies(float time_us)
{
	for (auto& it : enemies) {
		//if the enemy is alive update it
		//std::cout << (it.second ? "true" : "false") << "\n";
		if (it.second) {
			it.first.update(time_us);
			if (it.first.isInRadius(player.getRect())) {
				switch (it.first.getType())
				{
				case Enemy::ROTATING:
					//do a rotate thing
					rotating = true;
					previousPlayerRot = player.getRot();
					levelRotation += 90;
					playerRot -= 90;
					noRotates++;
					player.setCanRotate(false);
					player.lockRotate();
					break;
				case Enemy::SHOOTING:
				{
					//add projectile
					Projectile tempProjectile(it.first.getPos());
					tempProjectile.setDirection(player.getPos() - it.first.getPos());
					projectiles.push_back(tempProjectile);
				}
				default:
					break;
				}
			}

#if _DEV
			if (it.first.isInRadius(player.getRect())) {
				//std::cout << "ATTACK!\n";
				it.first.setRadiusColour(Game2D::Colour(1, 0, 1, 0.7));
			}
			else { it.first.setRadiusColour(Game2D::Colour(0, 1, 1, 0.7)); }
#endif
			//std::cout << "checking\n";
			//check to make sure the head is on the top relative to the player
			if (enemyAligned(it.first.getHead()) && (checkCollision(player.getFootbox(), it.first.getHeadBox()) || checkCollision(it.first.getHeadBox(), player.getFootbox()))) {
				//std::cout << "Dead\n";
				it.second = false;//it has been killed
				player.velocityY = 3 * moveSpeedY / 4.0f;
				player.unlockRotate();
				player.setCanRotate(true);
				//add death animation to animated sprite
				addDeathAnim(it.first.getPos(), it.first.getColour());
				//std::cout << "Adding death anims\n";
			}
			else if (checkCollision(it.first, player) || checkCollision(player, it.first)) {
				return true;
			}
		}
	}

	return false;
}

void Level::processProjectiles(float time_us) 
{
	std::vector<GameObject> solidObjects = walls;
	solidObjects.insert(solidObjects.end(), movingPlatforms.begin(), movingPlatforms.end());

	//has to be a better way than a double nested for loop
	for (auto it = projectiles.begin(); it != projectiles.end(); it++) {
		it->update(time_us);
		if (checkCollision(*it, player) || checkCollision(player, *it)) {
			//projectile has hit wall remove it
			projectiles.erase(it);
			it--;
			levelState = DYING;
			//init();//player has been hit with a projectile restart the level
			continue;
		}
		for (auto& it2 : solidObjects) {
			if (checkCollision(*it, it2) || checkCollision(it2, *it)) {
				//projectile has hit wall remove it
				projectiles.erase(it);
				it--;
				//std::cout << "Removing projectile\n";
			}
			//else if colliding with player kill them
		}
	}
}

void Level::processAnimatedSprites(float time_us)
{
	for (auto it = animatedSprites.begin(); it != animatedSprites.end(); it++) {
		if (it->update(time_us)) {
			animatedSprites.erase(it);
			it--;
		}
	}
}

bool Level::enemyAligned(Enemy::Direction dir) {
	if (dir == Enemy::NONE) { return false; } // enemy dosen't have a head so it will always be false
	float tempRot = levelRotation;
	if (tempRot == 360) { tempRot = 0; }

	if (((((int)dir) - 1) * 90) == tempRot) {
		return true;
	}

	return false;
}

void Level::addDeathAnim(Game2D::Pos2 pos, Game2D::Colour colour)
{
	animatedSprites.push_back(Game2D::AnimatedSprite(Game2D::Sprite(Game2D::Rect(pos, 10, 10), Game2D::Rect(0.11f, 0.0f, 0.2f, 0.19f))));
	animatedSprites.back().addFrame(Game2D::Sprite(Game2D::Rect(pos, 10, 10), Game2D::Rect(0.11f, 0.19f, 0.19f, -0.19f)));
	animatedSprites.back().addFrame(Game2D::Sprite(Game2D::Rect(pos, 10, 10), Game2D::Rect(0.30f, 0.00f, 0.19f, +0.19f)));
	animatedSprites.back().addFrame(Game2D::Sprite(Game2D::Rect(pos, 10, 10), Game2D::Rect(0.30f, 0.19f, 0.19f, -0.19f)));
	animatedSprites.back().addFrame(Game2D::Sprite(Game2D::Rect(pos, 10, 10), Game2D::Rect(0.50f, 0.00f, 0.19f, +0.19f)));
	animatedSprites.back().addFrame(Game2D::Sprite(Game2D::Rect(pos, 10, 10), Game2D::Rect(0.50f, 0.19f, 0.19f, -0.19f)));
	animatedSprites.back().addFrame(Game2D::Sprite(Game2D::Rect(pos, 10, 10), Game2D::Rect(0.70f, 0.00f, 0.19f, +0.19f)));
	animatedSprites.back().addFrame(Game2D::Sprite(Game2D::Rect(pos, 10, 10), Game2D::Rect(0.70f, 0.19f, 0.19f, -0.19f)));
	animatedSprites.back().addFrame(Game2D::Sprite(Game2D::Rect(pos, 10, 10), Game2D::Rect(0.90f, 0.00f, 0.00f, +0.00f)));
	//animatedSprites.back().setFrameTime(0.125f);
	animatedSprites.back().setFrameTime(0.125f);
	//animatedSprites.back().reset();
	animatedSprites.back().setLooping(false);
	animatedSprites.back().setPlayDirection(Game2D::Forward);
	animatedSprites.back().setColour(colour);
	animatedSprites.back().setFrame(0);
	animatedSprites.back().setElapsedTimeToZero();
	animatedSprites.back().play();
}

int Level::update(const InputManager& actions)
{
	endTime = Time::now();
	float elapsedTime = std::chrono::duration_cast<Microseconds>(endTime - startTime).count() / 1000000.0f;
	elapsedLevelTime += elapsedTime;
	//checkRotate();
	
	if (levelState == DYING) {
		//std::cout << elapsedTime << "\n";
		processAnimatedSprites(elapsedTime);
		if (playerDeathAnim.update(elapsedTime)) {
			return 2;
		}
		//std::cout << playerDeathAnim.getElapsedTime() << "\n";
		//std::cout << playerDeathAnim.getFrameTime() << "\n";
	} else if (rotating) {
		rotateTime += elapsedTime;
		if (std::abs(levelRotation - previousRot) > 90) {
			previousRot += 360 * (levelRotation - previousRot > 0 ? 1 : -1);
		}
		drawRot = previousRot + ((levelRotation-previousRot) * (rotateTime / 1.0f));
		player.setRot(previousPlayerRot + (playerRot - previousPlayerRot) * (rotateTime / 1.0f));
		//checkPlayerCollision(elapsedTime);
		//drawRot = (levelRotation / previousRot) * rotateTime;

		if (rotateTime > 1) {
			rotateTime = 0;
			rotating = false;
			drawRot = previousRot = levelRotation;
			if (playerRot > 360) { playerRot -= 360; }
			if (playerRot < 0) { playerRot += 360; }
			player.setRot(playerRot);
			applyGravity(elapsedTime);
			checkPlayerCollision(elapsedTime);
			player.velocityY = 0;
			//player.inAir = true;
		}
	} else {
		processActions(actions, elapsedTime);

		if (rotating) { return 0; }

		
		applyGravity(elapsedTime);
		processMovingPlatforms(elapsedTime);
		checkPlayerCollision(elapsedTime);
		if (processEnemies(elapsedTime)) {
			//init();
			levelState = DYING;
		}
		processProjectiles(elapsedTime);
		processAnimatedSprites(elapsedTime);
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
			//init();
			levelState = DYING;
		}
		if (exit.isInside(player.getRect())) {
			std::cout << "Level Done!\n";
			return 1;
		}

		if (levelState == DYING) {
			//init();
			//return 2;
			//addDeathAnim(player.getPos(), player.getColour());
			playerDeathAnim = Game2D::AnimatedSprite(Game2D::Sprite(Game2D::Rect(player.getPos(), 10, 10), Game2D::Rect(0.11f, 0.0f, 0.2f, 0.19f)));
			playerDeathAnim.addFrame(Game2D::Sprite(Game2D::Rect(player.getPos(), 10, 10), Game2D::Rect(0.11f, 0.19f, 0.19f, -0.19f)));
			playerDeathAnim.addFrame(Game2D::Sprite(Game2D::Rect(player.getPos(), 10, 10), Game2D::Rect(0.30f, 0.00f, 0.19f, +0.19f)));
			playerDeathAnim.addFrame(Game2D::Sprite(Game2D::Rect(player.getPos(), 10, 10), Game2D::Rect(0.30f, 0.19f, 0.19f, -0.19f)));
			playerDeathAnim.addFrame(Game2D::Sprite(Game2D::Rect(player.getPos(), 10, 10), Game2D::Rect(0.50f, 0.00f, 0.19f, +0.19f)));
			playerDeathAnim.addFrame(Game2D::Sprite(Game2D::Rect(player.getPos(), 10, 10), Game2D::Rect(0.50f, 0.19f, 0.19f, -0.19f)));
			playerDeathAnim.addFrame(Game2D::Sprite(Game2D::Rect(player.getPos(), 10, 10), Game2D::Rect(0.70f, 0.00f, 0.19f, +0.19f)));
			playerDeathAnim.addFrame(Game2D::Sprite(Game2D::Rect(player.getPos(), 10, 10), Game2D::Rect(0.70f, 0.19f, 0.19f, -0.19f)));
			playerDeathAnim.addFrame(Game2D::Sprite(Game2D::Rect(player.getPos(), 10, 10), Game2D::Rect(0.90f, 0.00f, 0.00f, +0.00f)));
			//playerDeathAnim.setFrameTime(0.125f);
			playerDeathAnim.setFrameTime(0.125f);
			//playerDeathAnim.reset();
			playerDeathAnim.setLooping(false);
			playerDeathAnim.setPlayDirection(Game2D::Forward);
			playerDeathAnim.setColour(player.getColour());
			playerDeathAnim.setFrame(0);
			playerDeathAnim.setElapsedTimeToZero();
			playerDeathAnim.play();
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
	levelState = PLAYING;
	panX = panY = 0;
	drawRot = previousRot = levelRotation = 0;
	player.setPos(startPos);
	rotating = false;
	rotateTime = 0;
	playerRot = previousPlayerRot = 0;
	player.setRot(0);
	noRotates = 0;
	elapsedLevelTime = 0.0f;
	player.velocityX = 0;
	player.velocityY = 0;
	for (auto& it : movingPlatforms) {
		it.reset();
	}
	for (auto& it : enemies) {
		it.first.reset();
		it.second = true;//set all the enimies to alive
	}
	projectiles.clear();//remove all projectiles
	animatedSprites.clear();
}

void Level::setActionLockOut(const InputManager& actions)
{
	for (int i = 0; i < 7; i++) {
		lockedKeys[i] = (actions.getAction(i) == InputManager::DOWN);
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

	//std::cout << projectiles.size() << "\n";
	for (const auto& it : projectiles) {
		it.draw();
		//std::cout << "Drawing projectile at " << it.getPos() << "\n";
	}

	for (auto it : enemies) {
		if (it.second) {
			it.first.draw();
		}
	}

#if _DEV
	if (Debug::getDrawHitboxes()) {
		for (auto it : killPlanes) {
			Game2D::Sprite temp(it);
			temp.setColour(Game2D::Colour(1, 0, 0, 0.5f));
			temp.draw();
		}
	}
#endif

	if (levelState == DYING) {
		playerDeathAnim.draw();
	} else {
		player.draw();
	}

	for (const auto& it : animatedSprites) {
		it.draw();
	}

	for (auto& it : noRotateZones) {
		it.draw();
	}

	glPopMatrix();

	Game2D::Colour(1, 1, 1).draw();
	Game2D::ScreenCoord::alignLeft();
	freetype::print(Game2D::Font::getFont(20), 2.5, 45, "Rotates:    %d", noRotates);
	freetype::print(Game2D::Font::getFont(20), 2.5, 40, "Time:    %2.2f", elapsedLevelTime);
	//std::cout << Game2D::ScreenCoord::getAspectRatio() << "\n";
	//std::cout << (5 * (Game2D::ScreenCoord::getAspectRatio() / (1.77778f))) << "\n";
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