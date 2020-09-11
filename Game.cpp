#include "Game.h"

Game::GameState Game::currentState;
std::map<int,bool> Game::keyMap;
GLFWwindow* Game::window;
int Game::screenWidth, Game::screenHeight;
Game2D::Button Game::testButton;
Game2D::Pos2 Game::mousePos;
std::map<int,Game2D::KeyState> Game::mouseButtons;
//Game2D::KeyMap Game::mouseButtons;
std::map<int,Game2D::KeyState::State> Game::previousMouseStates;
MainMenu Game::mainMenu;
//Level Game::testLevel;
InputManager Game::inputManager;
int Game::currentLevel;
std::vector<Level> Game::levels;
LevelSelect Game::levelSelect;

Game::Game()
{
	screenWidth = 1280;
	screenHeight = 720;
	mousePos = Game2D::Pos2(screenWidth,screenHeight);
	currentState = MAIN_MENU;

	//Key actions
	inputManager.addAction(Level::PLAYER_LEFT,GLFW_KEY_A);
	inputManager.addAction(Level::PLAYER_RIGHT,GLFW_KEY_D);
	inputManager.addAction(Level::PLAYER_JUMP,GLFW_KEY_W);

	inputManager.addAction(Level::RESET,GLFW_KEY_R);
	inputManager.addAction(Level::ROTATE_CLOCKWISE,GLFW_KEY_E);
	inputManager.addAction(Level::ROTATE_ANTICLOCKWISE,GLFW_KEY_Q);
	//!Key actions

	Game2D::ScreenCoord::init(screenWidth, screenHeight);
	currentLevel = 0;
}

void Game::loadLevelsFromFile()
{
	//on linux the directorys  are in a random order will need to read in all levels sort them then load in the levels
	for (auto it : std::filesystem::directory_iterator("levels")) {
		levels.push_back(Level());

		std::ifstream levelFile;
		levelFile.open(it.path());

		std::cout << it.path() << "\n";

		std::string line;
		std::getline(levelFile, line);

		float a, b;

		Game2D::Pos2 playerStartPos;
		std::sscanf(line.c_str(), "%f %f", &a, &b);

		playerStartPos.x = a;
		playerStartPos.y = b;

		levels.back().setStartPos(playerStartPos);

		std::getline(levelFile, line);
		Game2D::Rect exitRect;
		int exitType;
		std::sscanf(line.c_str(), "%f %f %d", &a, &b, &exitType);

		exitRect.pos.x = a;
		exitRect.pos.y = b;

		if (exitType == 0) {
			exitRect.width = 6;
			exitRect.height = 11;
		} else {
			exitRect.width = 11;
			exitRect.height = 6;
		}

		//std::cout << playerStartPos << "\t" << exitRect << "\n";

		levels.back().setExitRext(exitRect);

		/*
		*player start pos
		*exit rect
		*0 - wall
		*1 - kill plane
		*/
		while (std::getline(levelFile, line)) {
			float a, b, c, d, e, f, g, h;
			switch (line[0])
			{
			case '0':				
				std::sscanf(line.c_str(), "%f %f %f %f %f", &e, &a, &b, &c, &d);
				levels.back().addWall(Game2D::Rect(a, b, c, d));
				break;
			case '1':
				std::sscanf(line.c_str(), "%f %f %f %f %f %f %f", &e, &a, &b, &c, &d);
				levels.back().addKillPlane(Game2D::Rect(a, b, c, d));
				break;
			case '2':
				std::sscanf(line.c_str(), "%f %f %f %f %f %f", &e, &a, &b, &c, &d, &f, &g, &h);
				MovingPlatform platform(Game2D::Rect(a, b, c, d));
				platform.setEndPos(Game2D::Pos2(g, h));
				platform.setTravelTime(f);
				levels.back().addMovingPlatform(platform);
				break;
			}
		}
	}
#ifdef _DEV
	std::cout << levels.size() << " levels loaded\n";
#endif // _DEV
}

void Game::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.118f, 0.118f, 0.118f,1.0f);

	glLoadIdentity();

	switch (currentState)
	{
		case PLAYING:
			levels.at(currentLevel).draw();
			break;
		case PAUSED:
			break;
		case LEVEL_SELECT:
			levelSelect.draw();
			break;
		case MAIN_MENU:
			mainMenu.draw();
			break;
		case OPTIONS_MENU:
			break;
		case VICTORY:
			break;
		case LOSS:
			break;
		case QUITTING:
			break;
		default:
			break;
	}

	glDisable(GL_BLEND);
	glFlush();
}

void Game::init()
{
//	glfwSetWindowSizeCallback(window, reshape);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	mouseButtons.insert(std::pair<int,Game2D::KeyState>(GLFW_MOUSE_BUTTON_LEFT,Game2D::KeyState()));
	previousMouseStates.insert(std::pair<int,Game2D::KeyState::State>(GLFW_MOUSE_BUTTON_LEFT,Game2D::KeyState::UP));

	testButton = Game2D::Button(Game2D::Rect(25,25,20,10));
	Game2D::Sprite red = Game2D::Sprite(Game2D::Rect(25,25,20,10));
	red.setColour(Game2D::Colour::Red);
	Game2D::Sprite yellow = Game2D::Sprite(Game2D::Rect(25,25,20,10));
	yellow.setColour(Game2D::Colour::Yellow);
	Game2D::Sprite green = Game2D::Sprite(Game2D::Rect(25,25,20,10));
	green.setColour(Game2D::Colour::Green);
	Game2D::Sprite blue = Game2D::Sprite(Game2D::Rect(25,25,20,10));
	blue.setColour(Game2D::Colour::Blue);
	testButton.addStateSprites(red,yellow,green,blue,red);

	levels.at(currentLevel).init();

	//fonts
	Game2D::Font::init(screenHeight);
	Game2D::Font::insert(20);
	Game2D::Font::initFonts();
	//!fonts

	//textures
	TextureManager::loadTextures("textures/buttonSprites.png", 1);
	//!textures

	levelSelect.init(levels.size());
}

void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	try
	{
		if (action == GLFW_PRESS)
			inputManager.updateKeys(key, true);
		else if (action == GLFW_RELEASE)
			inputManager.updateKeys(key, false);
	}catch(...) {}//if a non mapped key is pressed do nothing
}

void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	/*
	try
	{
		if(action == GLFW_PRESS) mouseButtons.update(button,true);
		else if(action == GLFW_RELEASE) mouseButtons.update(button,false);
	}catch(...) {}*/
	try
	{
		if(action == GLFW_PRESS) mouseButtons.at(button).update(true);
		else if(action == GLFW_RELEASE) mouseButtons.at(button).update(false);
		//std::cout << mouseButtons.at(button).getState() << "\n";
	}catch(...) {}
}

void Game::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	mousePos = Game2D::Pos2(
			((xpos/screenWidth) * 100.0f * (screenWidth / (float)screenHeight))-((100.0f * (screenWidth / (float)screenHeight))/2.0f),
			(((screenHeight - ypos)/screenHeight)*100)-50);
}

void Game::processKeys()
{
	for(auto it = previousMouseStates.begin(); it != previousMouseStates.end();it++)
	{
		if (it->second == Game2D::KeyState::RELEASED)
			mouseButtons.at(it->first).update(false);

		it->second = mouseButtons.at(it->first).getState();
	}
}

void Game::processMouse()
{
}

void Game::update()
{
	//endTime = Time::now();
	//testButton.update(mousePos,mouseButtons.at(GLFW_MOUSE_BUTTON_LEFT).getState(),1);
	//auto temp = std::chrono::duration<Microseconds>(endTime - startTime);
	//elapsedTime = std::chrono::duration_cast<Microseconds>(endTime - startTime).count() / 1000000.0f;
//	std::cout << "elapsedTime:\t" << elapsedTime << "\n";
	switch (currentState)
	{
		case PLAYING:
			inputManager.update();
			//testLevel.update(inputManager);
			switch (levels.at(currentLevel).update(inputManager)) {
			case 1:
				if (++currentLevel == levels.size()) {
					currentState = MAIN_MENU;
					currentLevel = 0;
					break;
				}
				levels.at(currentLevel).init();
				break;
			default:
				break;
			}
			break;
		case PAUSED:
			break;
		case LEVEL_SELECT:
		{
			int result = levelSelect.update(mousePos, mouseButtons.at(GLFW_MOUSE_BUTTON_LEFT).getState(), 1);
			switch (result)
			{
			case -1:
				break;
			case -2:
				currentState = MAIN_MENU;
				break;
			default:
				currentLevel = result;
				levels.at(currentLevel).init();
				currentState = PLAYING;
				break;
			}
			break;
		}
		case MAIN_MENU:
			processMainMenu();
			break;
		case OPTIONS_MENU:
			break;
		case VICTORY:
			break;
		case LOSS:
			break;
		case QUITTING:
			break;
		default:
			std::cerr << "We're in an invalid game state" << std::endl;
			break;
	}
}

bool Game::createWindow()
{
	if (!glfwInit())
	{
		std::cerr << "failed to init glfw with error: 0x" << std::hex << std::setw(8) << std::setfill('0') << glfwGetError(NULL) << "\n";
		return false;
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(screenWidth, screenHeight, "Rotate", NULL, NULL);
	if (!window)
	{
		std::cerr << "failed to create window\n";
		glfwTerminate();
		return false;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//set screen coords
	//glOrtho(0, 100.0f * (screenWidth / (float)screenHeight), 0, 100, 0, 100);
	float coordWidth = (100.0f * (screenWidth / (float)screenHeight))/2.0f;
	glOrtho(-coordWidth, +coordWidth, -50, 50, -50, 50);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//TODO add in input class
	//input.setWindow(window);
	return true;
}

void Game::processMainMenu()
{
	mainMenu.update(mousePos, mouseButtons.at(GLFW_MOUSE_BUTTON_LEFT).getState(), 1);
	switch (mainMenu.getResult())
	{
		case 1:
			//testLevel.init();
			levels.at(currentLevel).init();
			currentState = LEVEL_SELECT;
			//currentState = PLAYING;
			break;
		case 2:
			currentState = OPTIONS_MENU;
			break;
		case 3:
			currentState = QUITTING;
			break;
	}
}

int Game::mainLoop()
{
	if(!createWindow())
		return -1;

	glfwSwapInterval(1);

	loadLevelsFromFile();

	init();

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		display();

		glfwSwapBuffers(window);

		update();
		//update glfw's mouse and keyboard events
		glfwPollEvents();
		processKeys();
		processMouse();

		if(currentState == QUITTING) break;
	}

	glfwTerminate();
	return 0;
}