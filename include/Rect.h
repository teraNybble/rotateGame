#ifndef RECT_H
#define RECT_H

#include "Pos2.h"

namespace Game2D
{

	class Rect
	{
	public:
		Rect();
		Rect(Pos2 p, float width, float height);
		Rect(float x, float y, float width, float height);

		float width, height;
		Pos2 pos;

		inline bool contains(Pos2 p)
		{
			return (((p.x > pos.x && p.x < pos.x + width) || (p.x < pos.x && p.x > pos.x + width))
					&& ((p.y > pos.y && p.y < pos.y + height)||(p.y < pos.y && p.y > pos.y + height)));
		}
	};

	inline std::ostream& operator<< (std::ostream& os, const Rect& r)
	{
		return os << r.pos << " W: " << r.width << " H: " << r.height;
	}
}

#endif //RECT_H