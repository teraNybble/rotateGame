#include "MainMenu.h"

MainMenu::MainMenu()
{
	play	= Game2D::Button(Game2D::Rect(0,-10,20,10));
	options	= Game2D::Button(Game2D::Rect(0,-20,20,10));
	quit	= Game2D::Button(Game2D::Rect(0,-30,20,10));

	/*
	Game2D::Sprite red = Game2D::Sprite(Game2D::Rect(0,0,10,5));
	red.setColour(Game2D::Colour::Red);
	Game2D::Sprite yellow = Game2D::Sprite(Game2D::Rect(0,0,10,5));
	yellow.setColour(Game2D::Colour::Yellow);
	Game2D::Sprite green = Game2D::Sprite(Game2D::Rect(0,0,10,5));
	green.setColour(Game2D::Colour::Green);
	Game2D::Sprite blue = Game2D::Sprite(Game2D::Rect(0,0,10,5));
	blue.setColour(Game2D::Colour::Blue);
	*/

	Game2D::Rect texRect(Game2D::Rect(0, 0, 0.1455f, 0.0762f));

	Game2D::AnimatedSprite playSprites(Game2D::Rect(0, -10, 20, 10));
	for (int i = 0; i < 4; i++) {
		Game2D::Sprite tempSprite(Game2D::Rect(0, -10, 20, 10));
		tempSprite.setColour(Game2D::Colour::White);
		Game2D::Rect tempRect = texRect;
		//the play buton is the 4th sprite along
		tempRect.pos.x = 3 * texRect.width;
		tempRect.pos.y = i * texRect.height;
		tempSprite.setTextureCoords(tempRect);
		playSprites.addFrame(tempSprite);
	}
	playSprites.setFrameTime(0);
	//what fram of the animation eath state starts at
	int temp[5] = { 0,1,2,3,4 };
	play.addAnims(playSprites, temp);

	Game2D::AnimatedSprite optionsSprites(Game2D::Rect(0, -20, 20, 10));
	for (int i = 0; i < 4; i++) {
		Game2D::Sprite tempSprite(Game2D::Rect(0, -20, 20, 10));
		tempSprite.setColour(Game2D::Colour::White);
		Game2D::Rect tempRect = texRect;
		//the options buton is the 5th sprite along
		tempRect.pos.x =4 * texRect.width;
		tempRect.pos.y = i * texRect.height;
		tempSprite.setTextureCoords(tempRect);
		optionsSprites.addFrame(tempSprite);
	}
	optionsSprites.setFrameTime(0);
	options.addAnims(optionsSprites, temp);

	Game2D::AnimatedSprite quitSprites(Game2D::Rect(0, -30, 20, 10));
	for (int i = 0; i < 4; i++) {
		Game2D::Sprite tempSprite(Game2D::Rect(0, -30, 20, 10));
		tempSprite.setColour(Game2D::Colour::White);
		Game2D::Rect tempRect = texRect;
		//the quit buton is the 2nd sprite along
		tempRect.pos.x = 1 * texRect.width;
		tempRect.pos.y = i * texRect.height;
		tempSprite.setTextureCoords(tempRect);
		quitSprites.addFrame(tempSprite);
	}
	quitSprites.setFrameTime(0);
	quit.addAnims(quitSprites, temp);

	//play.addStateSprites(red,yellow,green,blue,red);
	/*red.setPos(Game2D::Pos2(0,-7));
	yellow.setPos(Game2D::Pos2(0,-7));
	green.setPos(Game2D::Pos2(0,-7));
	blue.setPos(Game2D::Pos2(0,-7));
	options.addStateSprites(red,yellow,green,blue,red);
	red.setPos(Game2D::Pos2(0,-14));
	yellow.setPos(Game2D::Pos2(0,-14));
	green.setPos(Game2D::Pos2(0,-14));
	blue.setPos(Game2D::Pos2(0,-14));
	quit.addStateSprites(red,yellow,green,blue,red);*/
}

void MainMenu::update(Game2D::Pos2 mousePos, Game2D::KeyState::State state, float time)
{
	play.update(mousePos,state,time);
	options.update(mousePos,state,time);
	quit.update(mousePos,state,time);
}

int MainMenu::getResult()
{
	if (play.getState() == Game2D::ClickableObject::CLICK) 		return 1;
	if (options.getState() == Game2D::ClickableObject::CLICK)	return 2;
	if (quit.getState() == Game2D::ClickableObject::CLICK) 		return 3;

	return 0;
}

void MainMenu::draw()
{
	play.draw();
	options.draw();
	quit.draw();

//	freetype::print(Game2D::Font::getFont(20), 30, 30, "Test text");
}