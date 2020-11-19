#ifndef COLOUR_H
#define COLOUR_H

#include <ostream>
#include "glew.h"

namespace Game2D
{
	class Colour
	{
	private:
		float r, g, b, a;
	public:
		Colour();
		Colour(float r, float g, float b, float a = 1);

		static const Colour Black;
		static const Colour White;
		static const Colour Transparent;
		static const Colour Red;
		static const Colour Yellow;
		static const Colour Green;
		static const Colour Cyan;
		static const Colour Blue;
		static const Colour Magenta;

		inline void draw() const { glColor4f(r, g, b, a); }

		inline friend std::ostream& operator<<(std::ostream& os, const Colour& c)
		{
			return os << c.r << ", " << c.g << ", " << c.b << ", " << c.a;
		}
	};
}

#endif //COLOUR_H