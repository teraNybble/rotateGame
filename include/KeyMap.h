#ifndef G2D_KEYMAP_H
#define G2D_KEYMAP_H

#include "KeyState.h"
#include <map>

namespace Game2D
{
	class KeyMap
	{
	private:
		bool isDown;
		bool wasDown;
		KeyState::State currentState;

		std::map<int, KeyState> map;
	public:
		KeyMap();

		inline void addKey(int id) { map.insert(std::pair<int, KeyState>(id,KeyState())); }

		inline bool getDown() const { return isDown; }
		inline bool getWasDown() const { return wasDown; }
		inline KeyState::State getState() const { return currentState; }

		void update(int id, bool keyDown);
	};
}

#endif //G2D_KEYMAP_H