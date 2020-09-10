#ifndef BUTTON_H
#define BUTTON_H

//#include "freetype.h"
#include "ClickableObject.h"
#include "AnimatedSprite.h"

namespace Game2D
{
	class Button : public ClickableObject
	{
	private:
		//the different frames of the animation are the different states of the button
		//this allows there to be an animated transition between state if desired
		AnimatedSprite buttonAnims;
		int stateFrames[5];
		int currentFrame;
		int newFrame;

		int id;

		void fillFrameArray(int a[5]);
	public:
		Button();
		Button(Rect r);

		void addAnims(AnimatedSprite anims, int stateFrames[5]);
		void addStateSprites(Sprite none, Sprite hover, Sprite mouseDown, Sprite click, Sprite disable);

		inline int getCurrentFrame() const { return currentFrame; }

		ClickState update(Pos2 mousePos, KeyState::State state, float time);

		inline void setFrameTime(float time) { buttonAnims.setFrameTime(time); }

		inline void setID(int id) { this->id = id; }
		inline int getID() const { return id; }

		inline void debugDraw()
		{
			Game2D::Pos2 topLeft = Game2D::Pos2(getClickRegion().pos.x, getClickRegion().pos.y+getClickRegion().height);
			Game2D::Pos2 topRight = Game2D::Pos2(getClickRegion().pos.x + getClickRegion().width, getClickRegion().pos.y + getClickRegion().height);

			Game2D::Pos2 bottomLeft = Game2D::Pos2(getClickRegion().pos.x, getClickRegion().pos.y);
			Game2D::Pos2 bottomRight = Game2D::Pos2(getClickRegion().pos.x+getClickRegion().width, getClickRegion().pos.y);


			glPushMatrix();
			Game2D::Colour colour(0, 1, 1, 0.5f);
			colour.draw();

			//glTranslatef(rect.pos.x, rect.pos.y, 0);
			//glRotatef(rot, 0, 0, 1);

			glBegin(GL_POLYGON);
				glVertex2f(bottomLeft.x,bottomLeft.y);
				glVertex2f(topLeft.x,topLeft.y);
				glVertex2f(topRight.x,topRight.y);
				glVertex2f(bottomRight.x,bottomRight.y);
			glEnd();
			glPopMatrix();
		}

		void draw();
	};
}

#endif //BUTTON_H