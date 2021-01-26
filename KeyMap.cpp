#include "KeyMap.h"
#include <iostream>

KeyMap::KeyMap()
{
	this->isDown = this->wasDown = false;
}

KeyMap::~KeyMap()
{
	keys.clear();
}

void KeyMap::updateKeys(int key, bool down)
{
	try{
		keys.at(key) = down;
	}catch (...) {}
}

void KeyMap::update()
{
	for(auto it = keys.begin(); it != keys.end(); it++)
		if(it->second)		{
			isDown = true;
			return;
		}

	//if we get here then no key is down
	if(isDown)
	{
		isDown = false;
		wasDown = true;
	}
	else if(wasDown)
	{
		wasDown = false;
	}
}