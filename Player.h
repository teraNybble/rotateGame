#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
private:
	Game2D::Rect rotateBox;

	Game2D::Rect headBox;
	Game2D::Rect footBox;
public:
	Player();

	Game2D::Rect getRotateBox() const { return rotateBox; }

	void setPos(Game2D::Pos2 pos) { headBox.pos = pos; footBox.pos = pos; rotateBox.pos = pos; GameObject::setPos(pos); }
	void move(Game2D::Pos2 pos) { headBox.pos += pos; footBox.pos += pos; rotateBox.pos += pos; GameObject::move(pos); }
};

#endif //PLAYER_H