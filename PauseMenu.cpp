#include "PauseMenu.h"


void PauseMenu::init()
{
	back = Game2D::Button(Game2D::Rect(0, -10, 20, 10));
	menu = Game2D::Button(Game2D::Rect(0, -20, 20, 10));
	quit = Game2D::Button(Game2D::Rect(0, -30, 20, 10));

	Game2D::Rect texRect(Game2D::Rect(0, 0, 0.1455f, 0.0762f));

	Game2D::AnimatedSprite backSprites(Game2D::Rect(0, -10, 20, 10));
	for (int i = 0; i < 4; i++) {
		Game2D::Sprite tempSprite(Game2D::Rect(0, -10, 20, 10));
		tempSprite.setColour(Game2D::Colour::White);
		Game2D::Rect tempRect = texRect;
		//the play buton is the 4th sprite along
		tempRect.pos.x = 2 * texRect.width;
		tempRect.pos.y = (4 + i) * texRect.height;
		tempSprite.setTextureCoords(tempRect);
		backSprites.addFrame(tempSprite);
	}
	backSprites.setFrameTime(0);
	//what fram of the animation eath state starts at
	int temp[5] = { 0,1,2,3,4 };
	back.addAnims(backSprites, temp);

	Game2D::AnimatedSprite menuSprites(Game2D::Rect(0, -20, 20, 10));
	for (int i = 0; i < 4; i++) {
		Game2D::Sprite tempSprite(Game2D::Rect(0, -20, 20, 10));
		tempSprite.setColour(Game2D::Colour::White);
		Game2D::Rect tempRect = texRect;
		//the options buton is the 5th sprite along
		tempRect.pos.x = 2 * texRect.width;
		tempRect.pos.y = i * texRect.height;
		tempSprite.setTextureCoords(tempRect);
		menuSprites.addFrame(tempSprite);
	}
	menuSprites.setFrameTime(0);
	menu.addAnims(menuSprites, temp);

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

void PauseMenu::update(Game2D::Pos2 mousePos, Game2D::KeyState::State state, float time)
{
	back.update(mousePos, state, time);
	menu.update(mousePos, state, time);
	quit.update(mousePos, state, time);
}

int PauseMenu::getResult()
{
	if (back.getState() == Game2D::ClickableObject::CLICK) 	return 1;
	if (menu.getState() == Game2D::ClickableObject::CLICK)	return 2;
	if (quit.getState() == Game2D::ClickableObject::CLICK) 	return 3;

	return 0;
}

void PauseMenu::draw()
{
	glBindTexture(GL_TEXTURE_2D, TextureManager::getTexture(1));

	back.draw();
	menu.draw();
	quit.draw();
	//	freetype::print(Game2D::Font::getFont(20), 30, 30, "Test text");
}