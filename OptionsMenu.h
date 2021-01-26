#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "TextureManager.h"
#include <Button.h>
#include <Dropdown.h>
#include "Fonts.h"
#include <ScreenCoord.h>

class OptionsMenu
{
private:
	Game2D::Button play, back, apply;
	Game2D::Dropdown resolutions;
	Game2D::Dropdown aspectRatio;
	unsigned int previousAspect;

	void setResolutions(float ratio);
public:
	void init();

	void update(Game2D::Pos2 mousePos, Game2D::KeyState::State state, float time);
	int getResult(void(resize(float,float)));
	void draw();
};

#endif // !OPTIONSMENU_H