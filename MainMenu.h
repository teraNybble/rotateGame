#ifndef MAINMENU_H
#define MAINMENU_H

#include "TextureManager.h"
#include <Button.h>
#include "Fonts.h"

class MainMenu
{
private:
	Game2D::Button play,options,quit;
public:
	MainMenu();

	void update(Game2D::Pos2 mousePos, Game2D::KeyState::State state, float time);
	int getResult();
	void draw();
};


#endif //MAINMENU_H