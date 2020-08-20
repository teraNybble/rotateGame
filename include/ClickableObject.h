#ifndef CLICKABLEOBJECT_H
#define CLICKABLEOBJECT_H

#include "Rect.h"
#include "KeyState.h"

namespace Game2D
{
	class ClickableObject
	{
	public:
		enum ClickState { DISABLED, NONE, HOVER, MOUSEDOWN, CLICK };
	private:
		ClickState currentState;
		Rect clickRegion;
	public:
		ClickableObject();
		ClickableObject(Rect r);

		void alignToDrawableObject();

		inline void disable() { currentState = DISABLED; }
		inline void enable()  { currentState = NONE; }

		inline void overrigeState(ClickState state ) { currentState = state; }

		inline Rect getClickRegion() const { return clickRegion; }

		virtual inline void move(Pos2 p)     { clickRegion.pos += p; }
		virtual inline void setPos(Pos2 p)   { clickRegion.pos = p; }
		virtual inline void setRect(Rect r) { clickRegion = r; }
		virtual void setDimentions(float w, float h);

		inline ClickState getState() { return currentState; }
		virtual ClickState update(Pos2 mousePos, KeyState::State state);
	};

	inline std::ostream& operator<< (std::ostream& os,const ClickableObject::ClickState& cs)
	{
		switch(cs)
		{
			case ClickableObject::DISABLED:
				os << "DISABLED";
				break;
			case ClickableObject::NONE:
				os << "NONE";
				break;
			case ClickableObject::HOVER:
				os << "HOVER";
				break;
			case ClickableObject::MOUSEDOWN:
				os << "MOUSEDOWN";
				break;
			case ClickableObject::CLICK:
				os << "CLICK";
				break;
			default:
				os << "Not implemented yet";
				break;
		}

		return os;
	}
}

#endif //CLICKABLEOBJECT_H