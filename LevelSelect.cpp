#include "LevelSelect.h"

void LevelSelect::init(int noLevels)
{
	LevelSelect::noLevels = noLevels;
	float tempWidth = 0.04296875f;
	float tempPos = 0.0f;
	float tempSpacing = 41;
	float tempX = (-88.8 + (tempSpacing / 2.0f)) + ((177.7 - (tempSpacing * 4.0f)) / 2.0f);
	float tempY = 20;

	Game2D::Rect texRect(Game2D::Rect(0, 0, 0.1455f, 0.0762f));

	Game2D::AnimatedSprite backSprites(Game2D::Rect(20, -40, 20, 10));
	for (int i = 0; i < 4; i++) {
		Game2D::Sprite tempSprite(Game2D::Rect(20, -40, 20, 10));
		tempSprite.setColour(Game2D::Colour::White);
		Game2D::Rect tempRect = texRect;
		//the back buton is the 1st sprite along on the second row
		tempRect.pos.x = 0 * texRect.width;
		tempRect.pos.y = (i+4) * texRect.height;
		tempSprite.setTextureCoords(tempRect);
		backSprites.addFrame(tempSprite);
	}
	backSprites.setFrameTime(0);
	int tempFrames[5] = { 4,1,2,3,3 };

	buttons.push_back(Game2D::Button(Game2D::Rect(20, -40, 20, 10))); //back button
	buttons.back().addAnims(backSprites, tempFrames);

	Game2D::Rect arrowTexture(0, 0, 0.0752f, 0.0762f);

	Game2D::AnimatedSprite arrowSprites(Game2D::Rect(-30, -40, 10, 10));
	for (int i = 0; i < 4; i++) {
		Game2D::Sprite tempSprite(Game2D::Rect(-30, -40, 10, 10));
		tempSprite.setColour(Game2D::Colour::White);
		Game2D::Rect tempRect = arrowTexture;
		tempRect.pos.x = 0.8027f + arrowTexture.width;
		tempRect.width = -arrowTexture.width;
		tempRect.pos.y = i * arrowTexture.height;
		tempSprite.setTextureCoords(tempRect);
		arrowSprites.addFrame(tempSprite);
	}
	arrowSprites.setFrameTime(0);
	//what frame of the animation each state starts at
	buttons.push_back(Game2D::Button(Game2D::Rect(-30, -40, 10, 10)));//left arrow
	buttons.back().addAnims(arrowSprites, tempFrames);
	buttons.back().disable();

	Game2D::AnimatedSprite otherArrowSprites(Game2D::Rect(-18, -40, 10, 10));
	for (int i = 0; i < 4; i++) {
		Game2D::Sprite tempSprite(Game2D::Rect(-18, -40, 10, 10));
		tempSprite.setColour(Game2D::Colour::White);
		Game2D::Rect tempRect = arrowTexture;
		tempRect.pos.x = 0.8027f;
		tempRect.pos.y = i * arrowTexture.height;
		tempSprite.setTextureCoords(tempRect);
		otherArrowSprites.addFrame(tempSprite);
	}
	otherArrowSprites.setFrameTime(0);

	buttons.push_back(Game2D::Button(Game2D::Rect(-18, -40, 10, 10)));//right arrow
	buttons.back().addAnims(otherArrowSprites, tempFrames);


	std::vector<Game2D::Button> temp;

	Game2D::Rect levelRect(0, 0, 0.043f, 0.03125f);
	for (unsigned int i = 0; i < noLevels; i++)
	{
		Game2D::AnimatedSprite tempAnim(Game2D::Rect(tempX, tempY, tempSpacing, 27.0f));
		temp.push_back(Game2D::Button(Game2D::Rect(tempX, tempY, tempSpacing, 27.0f)));

		for (int j = 0; j < 4; j++) {
			Game2D::Sprite tempSprite(Game2D::Rect(tempX, tempY, tempSpacing, 27.0f));
			tempSprite.setColour(Game2D::Colour::White);
			Game2D::Rect tempRect = levelRect;
			//the quit buton is the 2nd sprite along
			tempRect.pos.y = j * levelRect.height;
			tempSprite.setTextureCoords(tempRect);
			tempAnim.addFrame(tempSprite);
		}
		tempAnim.setFrameTime(0);
		temp.back().addAnims(tempAnim, tempFrames);
		levelRect.pos.x += levelRect.width;

		tempX += tempSpacing;
		if (tempX >= (tempSpacing * 5) - tempX)
		{
			tempX = (-88.8 + (tempSpacing / 2.0f)) + ((177.7 - (tempSpacing * 4.0f)) / 2.0f);
			tempY -= 30;
		}
		tempPos += tempWidth;

		if (i % 7 == 0 && i != 0)
		{
			temp.shrink_to_fit();
			pages.push_back(temp);
			temp.clear();
			tempX = (-88.8 + (tempSpacing / 2.0f)) + ((177.7 - (tempSpacing * 4.0f)) / 2.0f);
			tempY = 20;
		}
	}
	temp.shrink_to_fit();

	if (temp.size() > 0)
		pages.push_back(temp);
		
}

int LevelSelect::update(Game2D::Pos2 mousePos, Game2D::KeyState::State state, float time)
{
	int i = 0;
	for (auto& it : pages.at(pageNo)) {
		if (it.update(mousePos, state, time) == Game2D::ClickableObject::CLICK) {
			return (8 * pageNo) + i;
		}
		i++;
	}

	Game2D::Pos2 leftMousePos = mousePos;
	leftMousePos.x += (50*Game2D::ScreenCoord::getAspectRatio());
	if (buttons[0].update(leftMousePos, state, time) == Game2D::ClickableObject::CLICK) {
		return -2;
	}
	Game2D::Pos2 rightMousePos = mousePos;
	rightMousePos.x -= (50 * Game2D::ScreenCoord::getAspectRatio());
	if (buttons[1].update(rightMousePos, state, time) == Game2D::ClickableObject::CLICK) {
		if (pageNo > 0) { 
			pageNo--; 
			if (pageNo == 0) { buttons[1].disable(); }
			if (pageNo < pages.size() - 1) { buttons[2].enable(); }
		}
	}
	if (buttons[2].update(rightMousePos, state, time) == Game2D::ClickableObject::CLICK) {
		if (pageNo < pages.size() - 1) { 
			pageNo++; 
			if (pageNo > 0) { buttons[1].enable(); }
			if (pageNo == pages.size() - 1) { buttons[2].disable(); }
		}
	}

	return -1;
}

void LevelSelect::draw()
{
	glBindTexture(GL_TEXTURE_2D, TextureManager::getTexture(1));
	//align the back button to the left 
	Game2D::ScreenCoord::alignLeft();
	for (auto& it : buttons) {
		it.draw();
		//align the page navigation buttons to the right
		Game2D::ScreenCoord::alignRight();
	}
	Game2D::ScreenCoord::alignCentre();
	
	glBindTexture(GL_TEXTURE_2D, TextureManager::getTexture(2));
	for (auto& it : pages.at(pageNo)) {
		it.draw();
	}
}