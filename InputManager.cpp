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
	//	std::cout << "succesfully added new key to ID " << id << "\n";
	}
	catch(...)
	{
		//the action doesn't exsist so add it
		actions.insert(std::pair<int,KeyMap>(id, KeyMap()));
		actions.at(id).addKey(key);
	//	std::cout << "succesfully created new action with ID " << id << "\n";
	}
}

InputManager::ActionState InputManager::getAction(int id) const
{
	try{ //try catch used incase someone uses an invaid id
		if(actions.at(id).getIsDown()) return ActionState::DOWN;
		if(actions.at(id).getWasDown()) return ActionState::WAS_DOWN;
	}catch (...){ std::cerr << "Invalid ID used with input manager" << std::endl; }

//	std::cout << "Returning none for id " << id << "\n";

	return ActionState::NONE;
}

void InputManager::updateKeys(int key, bool down)
{
	//std::cout << actions.size() << "\n";
	for (auto it = actions.begin(); it != actions.end(); it++) {
		it->second.updateKeys(key, down);
	}
}

void InputManager::update()
{
	for(auto it = actions.begin(); it != actions.end(); it++)
		it->second.update();
}