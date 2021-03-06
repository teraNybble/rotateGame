#include "MainMenu.h"

void MainMenu::init()
{
	play	= Game2D::Button(Game2D::Rect(0,-10,20,10));
	options	= Game2D::Button(Game2D::Rect(0,-20,20,10));
	quit	= Game2D::Button(Game2D::Rect(0,-30,20,10));

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
	//what frame of the animation each state starts at
	int temp[5] = { 0,1,2,3,4 };
	play.addAnims(playSprites, temp);

	Game2D::AnimatedSprite optionsSprites(Game2D::Rect(0, -20, 20, 10));
	for (int i = 0; i < 4; i++) {
		Game2D::Sprite tempSprite(Game2D::Rect(0, -20, 20, 10));
		tempSprite.setColour(Game2D::Colour::White);
		Game2D::Rect tempRect = texRect;
		//the options buton is the 5th sprite along
		tempRect.pos.x = 4 * texRect.width;
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
	glBindTexture(GL_TEXTURE_2D, TextureManager::getTexture(1));
	
	play.draw();
	options.draw();
	quit.draw();
	Game2D::ScreenCoord::alignRight();
	int length = freetype::getLength(Game2D::Font::getFont(3), VerNo);
	freetype::print(Game2D::Font::getFont(3), -5-length, -47, VerNo);
	Game2D::ScreenCoord::alignCentre();
}