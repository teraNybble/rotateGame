#ifndef KEYSTATE_H
#define KEYSTATE_H

#include <iostream>

namespace Game2D
{
	class KeyState
	{
	public:
		enum State { DOWN, RELEASED, UP };
		KeyState();

		inline bool getDown() const { return isDown; }
		inline bool getWasDown() const { return wasDown; }
		inline State getState() const { return currentState; }

		void update(bool keyDown);
	private:
		bool isDown, wasDown;
		State currentState;
	};

	inline std::ostream& operator<< (std::ostream& os, const KeyState::State& s)
	{
		switch (s)
		{
			case KeyState::DOWN:
				os << "DOWN";
				break;
			case KeyState::RELEASED:
				os << "RELEASED";
				break;
			case KeyState::UP:
				os << "UP";
				break;
			default:
				os << "not implemented";
				break;
		}
		return os;
	}
}

#endif //KEYSTATE_H