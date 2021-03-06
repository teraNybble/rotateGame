#ifndef MAINMENU_H
#define MAINMENU_H

#include "TextureManager.h"
#include <Button.h>
#include "Fonts.h"
#include <ScreenCoord.h>

#ifdef _DEV
#define VerNo "0.0.6(Dev)"
#else
#define VerNo "0.0.6"
#endif // _DEV


class MainMenu
{
private:
	Game2D::Button play,options,quit;
public:
	void init();

	void update(Game2D::Pos2 mousePos, Game2D::KeyState::State state, float time);
	int getResult();
	void draw();
};


#endif //MAINMENU_H