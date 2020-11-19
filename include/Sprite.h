#ifndef SPRITE_H
#define SPRITE_H

#include "DrawableObject.h"

namespace Game2D
{
	class Sprite : public DrawableObject
	{
	private:
	protected:
		bool loadedTex;
		Rect texture;
	public:
		Sprite();
		Sprite(Rect r);
		Sprite(Rect r, Rect texCoords);

		inline void setTextureCoords(Rect t) { texture = t; loadedTex = true; }

		inline bool textureLoaded() const { return loadedTex; }

		void flipX();
		void flipY();

		void draw() const;
	};
}

#endif //SPRITE_H