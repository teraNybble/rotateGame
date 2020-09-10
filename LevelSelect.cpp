#include "LevelSelect.h"

void LevelSelect::init(int noLevels)
{
	this->noLevels = noLevels;
	float tempWidth = 0.04296875f;
	float tempPos = 0.0f;
	float tempSpacing = 41;
	//-88 + tempspacing/2
	float tempX = (-88.8 + (tempSpacing / 2.0f)) + ((177.7 - (tempSpacing * 4.0f)) / 2.0f);
	//std::cout << tempX << "\n";
	//float tempX = -88.8 + (tempSpacing / 2.0f);
	//float tempX = -60;
	float tempY = 20;
	//menuTexture = loadPNG("Textures/LevelSelectSprites.png");

	Game2D::Sprite red = Game2D::Sprite(Game2D::Rect(20, -40, 20, 10));
	red.setColour(Game2D::Colour::Red);
	Game2D::Sprite yellow = Game2D::Sprite(Game2D::Rect(20, -40, 20, 10));
	yellow.setColour(Game2D::Colour::Yellow);
	Game2D::Sprite green = Game2D::Sprite(Game2D::Rect(20, -40, 20, 10));
	green.setColour(Game2D::Colour::Green);
	Game2D::Sprite blue = Game2D::Sprite(Game2D::Rect(20, -40, 20, 10));
	blue.setColour(Game2D::Colour::Blue);
	Game2D::Sprite grey = Game2D::Sprite(Game2D::Rect(20, -40, 20, 10));
	grey.setColour(Game2D::Colour(0.7,0.7,0.7));
	
	buttons.push_back(Game2D::Button(Game2D::Rect(20, -40, 20, 10))); //back button
	//buttons.back().setTextureCoords(Game2D::Rect(0.0f, 0.292f, 0.54296875f, 0.15234375f), 3);
	buttons.back().addStateSprites(red, yellow, green, blue, grey);

	red.setRect(Game2D::Rect(-30, -40, 10, 10));
	yellow.setRect(Game2D::Rect(-30, -40, 10, 10));
	green.setRect(Game2D::Rect(-30, -40, 10, 10));
	blue.setRect(Game2D::Rect(-30, -40, 10, 10));
	grey.setRect(Game2D::Rect(-30, -40, 10, 10));
	buttons.push_back(Game2D::Button(Game2D::Rect(-30, -40, 10, 10)));//left arrow
	//buttons.back().setTextureCoords(Game2D::Rect(0.292f, 0.150390625f, 0.390625f, 0.15234375f), 4);
	buttons.back().addStateSprites(red, yellow, green, blue, grey);
	buttons.back().disable();

	red.setPos(Game2D::Pos2(-18, -40));
	yellow.setPos(Game2D::Pos2(-18, -40));
	green.setPos(Game2D::Pos2(-18, -40));
	blue.setPos(Game2D::Pos2(-18, -40));
	grey.setPos(Game2D::Pos2(-18, -40));
	buttons.push_back(Game2D::Button(Game2D::Rect(-18, -40, 10, 10)));//right arrow
	buttons.back().addStateSprites(red, yellow, green, blue, grey);
	//buttons.back().setTextureCoords(Game2D::Rect(0.442390625f, 0.150390625f, 0.390625f, 0.15234375f), 4);

	std::vector<Game2D::Button> temp;
	for (unsigned int i = 0; i < /*Scores::noLevels*/noLevels; i++)
	{
		temp.push_back(Game2D::Button(Game2D::Rect(tempX, tempY, tempSpacing, 27.0f)));
		//temp.back().setTextureCoords(Game2D::Rect(tempPos, tempWidth, 0, 0.03125f), 4);
		red.setRect(Game2D::Rect(tempX, tempY, tempSpacing, 27.0f));
		yellow.setRect(Game2D::Rect(tempX, tempY, tempSpacing, 27.0f));
		green.setRect(Game2D::Rect(tempX, tempY, tempSpacing, 27.0f));
		blue.setRect(Game2D::Rect(tempX,  tempY, tempSpacing, 27.0f));
		temp.back().addStateSprites(red, yellow, green, blue, red);
		//if (i > Scores::getUnlockedLevels()) { temp.back().disable(); }

		tempX += tempSpacing;
		if (tempX >= (tempSpacing * 5) - tempX)
		{
			//tempX = -30;
			tempX = (-88.8 + (tempSpacing / 2.0f)) + ((177.7 - (tempSpacing * 4.0f)) / 2.0f);
			tempY -= 30;
		}
		tempPos += tempWidth;

		if (i % 7 == 0 && i != 0)
		{
			temp.shrink_to_fit();
			pages.push_back(temp);
			temp.clear();
			tempX = -30;
			tempY = 60;
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
	leftMousePos.x += (50*(16.0f/9.0f));
	if (buttons[0].update(leftMousePos, state, time) == Game2D::ClickableObject::CLICK) {
		return -2;
	}
	Game2D::Pos2 rightMousePos = mousePos;
	rightMousePos.x -= (50 * (16.0f / 9.0f));
	if (buttons[1].update(rightMousePos, state, time) == Game2D::ClickableObject::CLICK) {
		//return -3;
	}
	if (buttons[2].update(rightMousePos, state, time) == Game2D::ClickableObject::CLICK) {
		//return -4;
	}

	return -1;
}

void LevelSelect::draw()
{
	//align the back button to the left 
	Game2D::ScreenCoord::alignLeft();
	for (auto& it : buttons) {
		it.draw();
		//it.debugDraw();
		//align the page navigation buttons to the right
		Game2D::ScreenCoord::alignRight();
	}
	Game2D::ScreenCoord::alignCentre();
	
	for (auto& it : pages.at(pageNo)) {
		it.draw();
		//it.debugDraw();
	}
	

}