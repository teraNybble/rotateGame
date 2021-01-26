#include "InputManager.h"
#include <iostream>

InputManager::~InputManager()
{
	actions.clear();
}

void InputManager::addAction(int id, int key)
{
	try
	{
		//if the action exists already
		actions.at(id).addKey(key);
	}
	catch(...)
	{
		//the action doesn't exsist so add it
		actions.insert(std::pair<int,KeyMap>(id, KeyMap()));
		actions.at(id).addKey(key);
	}
}

InputManager::ActionState InputManager::getAction(int id) const
{
	try{ //try catch used incase someone uses an invaid id
		if(actions.at(id).getIsDown()) return ActionState::DOWN;
		if(actions.at(id).getWasDown()) return ActionState::WAS_DOWN;
	}catch (...){ std::cerr << "Invalid ID used with input manager" << std::endl; }

	return ActionState::NONE;
}

void InputManager::updateKeys(int key, bool down)
{
	for (auto it = actions.begin(); it != actions.end(); it++) {
		it->second.updateKeys(key, down);
	}
}

void InputManager::update()
{
	for(auto it = actions.begin(); it != actions.end(); it++)
		it->second.update();
}

void InputManager::setAllFalse()
{
	for (auto it = actions.begin(); it != actions.end(); it++) {
		it->second.setFalse();
	}
}