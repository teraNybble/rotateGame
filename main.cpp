#include "Game.h"
#include <chrono>

int main()
{

	/*
	std::string test = "69 420\n";

	int a, b;

	std::sscanf(test.c_str(),"%d %d", &a, &b);

	std::cout << a << " " << b << "\n";

	return 69;
	*/


#if _DEV
	std::cout << "Developer Build\n";
#endif
	Game game;

	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

	return game.mainLoop();
}