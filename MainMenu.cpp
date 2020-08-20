#include "MainMenu.h"

MainMenu::MainMenu()
{
	play	= Game2D::Button(Game2D::Rect(0,0,10,5));
	options	= Game2D::Button(Game2D::Rect(0,-7,10,5));
	quit	= Game2D::Button(Game2D::Rect(0,-14,10,5));

	Game2D::Sprite red = Game2D::Sprite(Game2D::Rect(0,0,10,5));
	red.setColour(Game2D::Colour::Red);
	Game2D::Sprite yellow = Game2D::Sprite(Game2D::Rect(0,0,10,5));
	yellow.setColour(Game2D::Colour::Yellow);
	Game2D::Sprite green = Game2D::Sprite(Game2D::Rect(0,0,10,5));
	green.setColour(Game2D::Colour::Green);
	Game2D::Sprite blue = Game2D::Sprite(Game2D::Rect(0,0,10,5));
	blue.setColour(Game2D::Colour::Blue);

	play.addStateSprites(red,yellow,green,blue,red);
	red.setPos(Game2D::Pos2(0,-7));
	yellow.setPos(Game2D::Pos2(0,-7));
	green.setPos(Game2D::Pos2(0,-7));
	blue.setPos(Game2D::Pos2(0,-7));
	options.addStateSprites(red,yellow,green,blue,red);
	red.setPos(Game2D::Pos2(0,-14));
	yellow.setPos(Game2D::Pos2(0,-14));
	green.setPos(Game2D::Pos2(0,-14));
	blue.setPos(Game2D::Pos2(0,-14));
	quit.addStateSprites(red,yellow,green,blue,red);
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