#ifndef LOSESCREEN_H
#define LOSESCREEN_H

#include <Button.h>
#include <ScreenCoord.h>
#include <Fonts.h>
#include "TextureManager.h"

class LoseScreen
{
private:
	Game2D::Button play, menu, quit;
public:
	//MainMenu();

	void init();

	void update(Game2D::Pos2 mousePos, Game2D::KeyState::State state, float time);
	int getResult();
	void draw();
};

#endif