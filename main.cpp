#include "Game.h"
#include <chrono>

int main()
{
#if _DEV
	std::cout << "Developer Build\n";
#endif
	Game game;

	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

	return game.mainLoop();
}