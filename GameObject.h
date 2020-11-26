#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Rect.h>
#include <Colour.h>
#include <Sprite.h>

class GameObject
{
private:
protected:
	//Game2D::Rect rect;
	//Game2D::Colour colour;
	float rot;
	Game2D::Rect hitBox;

	Game2D::Sprite sprite;
public:
	GameObject();
	GameObject(Game2D::Rect rect);

	float velocityX, velocityY;
	bool inAir;

	bool isInside(Game2D::Rect rect);

	inline void setPos(Game2D::Pos2 pos)			{ sprite.setPos(pos); hitBox.pos = pos; }
	inline void setRot(float rot)					{ this->rot = rot; sprite.setRot(rot); }
	inline void setRect(Game2D::Rect rect)			{ sprite.setRect(rect); hitBox = rect; }
	inline void setColour(Game2D::Colour colour) 	{ sprite.setColour(colour); }
	inline void setSprite(Game2D::Sprite sprite)	{ this->sprite = sprite; hitBox = sprite.getRect(); }

	inline void rotate(float rot)					{ this->rot += rot; sprite.rotate(rot); }
	inline void move(Game2D::Pos2 pos)				{ sprite.move(pos); hitBox.pos += pos; }

	inline float getRot()				const { return rot; }
	inline Game2D::Pos2 getPos() 		const { return hitBox.pos; }
	inline Game2D::Rect getRect() 		const { return hitBox; }
	inline Game2D::Colour getColour()	const { return sprite.getColour(); }
	//inline float& getVelocityX() { return velocityX; }
	//inline float& getVelocityY() { return velocityY; }
	inline Game2D::Pos2 getVelocity()	const { return Game2D::Pos2(velocityX, velocityY); }

	void moveSansRot(Game2D::Pos2 pos, float rot);

	void draw() const;
};


#endif //GAMEOBJECT_H