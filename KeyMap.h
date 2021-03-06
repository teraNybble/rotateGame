#ifndef KEYMAP_H
#define KEYMAP_H

#include <vector>
#include <map>

class KeyMap
{
private:
	bool isDown;
	bool wasDown;
	std::map<int, bool> keys;
public:
	KeyMap();
	~KeyMap();

	inline void addKey(int keyId) { keys.insert(std::pair<int,bool>(keyId,false)); }

	//to be used in a key callback
	void updateKeys(int key, bool down);

	void update();

	inline bool getIsDown() const { return isDown; }
	inline bool getWasDown() const { return wasDown; }

	inline void setFalse() { isDown = wasDown = false; }
};


#endif //KEYMAP_H