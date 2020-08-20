#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#undef KEYMAP_H
#include "KeyMap.h"

class InputManager
{
private:
	std::map<int, KeyMap> actions;
public:
	enum ActionState { NONE, DOWN, WAS_DOWN };

	//to be used in a keyCallback
	void updateKeys(int key, bool down);

	void update();

	void addAction(int id, int key);
	ActionState getAction(int id) const;
};


#endif //INPUTMANAGER_H