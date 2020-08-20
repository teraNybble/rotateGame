#include "KeyMap.h"
#include <iostream>

KeyMap::KeyMap()
{
	this->isDown = this->wasDown = false;
}

void KeyMap::updateKeys(int key, bool down)
{
	//std::cout << "setting key (" << key << ") to " << (down ? "true":"false") << "\n";
	try{
		keys.at(key) = down;
	}catch (...) {}
/*
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
 */
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