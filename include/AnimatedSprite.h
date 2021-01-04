#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"
#include <vector>

namespace Game2D
{
	typedef bool PlayDirection;
//#define Forward true
//#define Backward false
	constexpr PlayDirection Forward = true;
	constexpr PlayDirection Backward = false;

	class AnimatedSprite
	{
	private:
		bool looping;
		PlayDirection playDirection;
		bool playing;

		std::vector<Sprite> anim;
		unsigned int currentFrame;
		float frameTime;
		float elapsedTime;
	public:
		AnimatedSprite();
		AnimatedSprite(Sprite s);

		inline void addFrame(Sprite frame) { anim.push_back(frame); }
		inline void clearFrames() { anim.empty(); }

		inline void setFrame(unsigned int frame) {if(frame < anim.size()) currentFrame = frame; }
		inline unsigned int getFrame() const { return currentFrame; }
		inline void setFrameTime(float time) { frameTime = time; }
		inline void setColour(Game2D::Colour colour) { for (auto& it : anim) { it.setColour(colour); } }

		inline void setLooping(bool loop) { looping = loop; }
		inline void setPlayDirection(PlayDirection direction) { playDirection = direction; }

		inline void play() { playing = true; }
		inline void pause() { playing = false; }
		inline void reset() { AnimatedSprite(); }
		inline void setElapsedTimeToZero() { elapsedTime = 0.0f; }

		inline int getSize() const { return anim.size(); }

		inline void setPoss(Pos2 pos) { for (auto& it : anim) { it.setPos(pos); } }

		bool update(float time); //returns true if the sprite has finnished playing
		void draw() const;
	};
}

#endif //ANIMATEDSPRITE_H