#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "Rect.h"
#include "Colour.h"

namespace Game2D
{
	class DrawableObject
	{
	private:
	protected:
		float rot;
		Rect rect;
		Colour colour;
	public:
		DrawableObject();
		DrawableObject(Rect rec);

		virtual inline void move(Pos2 p) { rect.pos += p; }
		virtual inline void setPos(Pos2 p) { rect.pos = p; }
		virtual inline void setRect(Rect r) { rect = r; }
		virtual void setDimentions(float w, float h);

		inline Pos2 getPos() const { return rect.pos; }
		inline Rect getRect() const { return rect; }

		inline void rotate(float r) { rot += r; }
		inline void setRot(float r) { rot = r; }

		inline void setColour(Colour c) { colour = c; }
		inline Colour getColour() const { return colour; }

		virtual void draw();
	};
}

#endif //DRAWABLEOBJECT_H