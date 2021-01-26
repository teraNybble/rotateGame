#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "TextureManager.h"
#include <Button.h>
#include "Fonts.h"


class PauseMenu
{
private:
	Game2D::Button back, menu, quit;
public:
	void init();

	void update(Game2D::Pos2 mousePos, Game2D::KeyState::State state, float time);
	int getResult();
	void draw();
};

#endif // !PAUSEMENU_H