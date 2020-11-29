#ifndef GAME_H
#define GAME_H

//used for error output and formatting the message
#include <iostream>
#include <iomanip>
#include <map>
#include <Button.h>
#include <KeyMap.h>
//include glfw and glew
#include "glew.h"
#include <GLFW/glfw3.h>
#include "MainMenu.h"
#include "PauseMenu.h"
#include "LoseScreen.h"
#include "Level.h"
#include "Fonts.h"
#include <string>
#include <fstream>
#include <filesystem>
#include "LevelSelect.h"
#include "TextureManager.h"
//#include <experimental/filesystem>

#ifdef _DEV
#include "Debug.h"
#endif // _DEV

#define LEFT_MOUSE -1000

class Game
{
private:
	enum GameState { PLAYING, PAUSED, LEVEL_SELECT, MAIN_MENU, OPTIONS_MENU, VICTORY, LOSS, QUITTING };

	static GameState currentState;
	//static std::map<int,bool> keyMap;
	//static std::map<int,Game2D::KeyState> mouseButtons;
	//static std::map<int,Game2D::KeyState::State> previousMouseStates;
	//static Game2D::KeyMap mouseButtons;
	static Game2D::Pos2 mousePos;

	static GLFWwindow* window;
	static int screenWidth, screenHeight;
	static Game2D::Button testButton;
	static MainMenu mainMenu;
	static PauseMenu pauseMenu;
	static LoseScreen loseScreen;

	static InputManager inputManager;
	static InputManager mouseButtons;
	/*
	 * test code
	static GameObject testObject;
	static Player testPlayer;
	static Clock startTime;
	static Clock endTime;
	static float elapsedTime;
	//static Clock startTime;
	//static Clock endTime;
	 */
	//static Level testLevel;
	//static bool paused;
	static int currentLevel;
	static std::vector<Level> levels;
	//static int currentLevel;

	static LevelSelect levelSelect;

	static void loadLevelsFromFile();
public:
	Game();

	static void display();
	static void init();
	static void resize_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void processKeys();
	static void processMouse();
	static void update();
	static bool createWindow();

	static void processMainMenu();
	static void processPauseMenu();

	static int mainLoop();
};


#endif //GAME_H