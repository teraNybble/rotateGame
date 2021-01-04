#ifndef BUTTON_H
#define BUTTON_H

//#include "freetype.h"
#include "ClickableObject.h"
#include "AnimatedSprite.h"
#include <string>

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

		std::string text;
		unsigned int fontSize;
		Colour fontColour;

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

		inline void setText(std::string text) { this->text = text; }
		inline std::string getText() const { return text; }
		inline void setFontSize(unsigned int size) { fontSize = size; }
		inline void setFontColour(Colour c) { fontColour = c; }

		inline void setAnimPoss(Pos2 pos) { buttonAnims.setPoss(pos); }

		void draw() const;
	};
}

#endif //BUTTON_H