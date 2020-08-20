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

		void draw();
	};
}

#endif //BUTTON_H