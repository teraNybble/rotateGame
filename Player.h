#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
private:
	Game2D::Rect rotateBox;

	Game2D::Rect headBox;
	Game2D::Rect footBox;
	bool canRotate;
	bool rotateLock;
public:
	Player();

	Game2D::Rect getRotateBox() const { return rotateBox; }

	void setRot(float rot);
	void setPos(Game2D::Pos2 pos) { headBox.pos = pos; footBox.pos = pos; rotateBox.pos = pos; GameObject::setPos(pos); }
	void move(Game2D::Pos2 pos) { headBox.pos += pos; footBox.pos += pos; rotateBox.pos += pos; GameObject::move(pos); }
	void moveSansRot(Game2D::Pos2 pos, float rot);

	void setCanRotate(bool rotate);
	inline bool getCanRotate() const { return canRotate; }
	
	inline void lockRotate() { rotateLock = true; }
	inline void unlockRotate() { rotateLock = false; }
	/*
	inline void draw() {
		GameObject::draw(); 
		Game2D::Sprite temp(rotateBox);
		temp.setColour(Game2D::Colour(0, 1, 1, 0.5f));
		temp.draw();
	}
	*/
};

#endif //PLAYER_H