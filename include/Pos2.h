#ifndef POS2_H
#define POS2_H

//#include <ostream>
#include <iostream>

namespace Game2D
{
	class Pos2
	{
	public:
		Pos2();
		Pos2(float x, float y);

		float x, y;

		inline Pos2 operator+ (const Pos2 &p) const
		{
			return Pos2(x + p.x, y + p.y);
		}

		inline Pos2& operator+= (const Pos2 &p)
		{
			x += p.x;
			y += p.y;

			return *this;
		}

		inline Pos2 operator- (const Pos2 &p) const
		{
			return Pos2(x - p.x, y - p.y);
		}

		inline Pos2& operator-= (const Pos2 &p)
		{
			x -= p.x;
			y -= p.y;

			return *this;
		}
	};

	inline std::ostream& operator<< (std::ostream& os,const Pos2& p)
	{
		return os << p.x << ", " << p.y;
	}
}

#endif //POS2_H