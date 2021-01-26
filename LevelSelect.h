#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <ScreenCoord.h>
#include <vector>
#include <Button.h>
#include "TextureManager.h"

class LevelSelect
{
private:
	std::vector<Game2D::Button> buttons;
	std::vector<std::vector<Game2D::Button>> pages;
	int noLevels;
	int pageNo;
	int selectedItem;
public:
	void init(int noLevels);
	int update(Game2D::Pos2 mousePos, Game2D::KeyState::State state, float time);

	void draw();
};

#endif