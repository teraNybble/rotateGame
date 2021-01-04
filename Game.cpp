#include "Game.h"

Game::GameState Game::currentState;
//std::map<int,bool> Game::keyMap;
GLFWwindow* Game::window;
int Game::screenWidth, Game::screenHeight;
int Game::windowHintFlags;
Game2D::Button Game::testButton;
Game2D::Pos2 Game::mousePos;
//std::map<int,Game2D::KeyState> Game::mouseButtons;
//Game2D::KeyMap Game::mouseButtons;
//std::map<int,Game2D::KeyState::State> Game::previousMouseStates;
MainMenu Game::mainMenu;
OptionsMenu Game::optionsMenu;
PauseMenu Game::pauseMenu;
LoseScreen Game::loseScreen;
//Level Game::testLevel;
InputManager Game::inputManager;
InputManager Game::mouseButtons;
//bool Game::paused;
int Game::currentLevel;
std::vector<Level> Game::levels;
LevelSelect Game::levelSelect;

Game::Game()
{
	//std::cout << "Game constructor\n";
	//screenWidth = 1280;
	//screenHeight = 720;
	readDisplayConfig();
	//screenWidth = 1920;
	//screenHeight = 1080;
	mousePos = Game2D::Pos2(screenWidth,screenHeight);
	currentState = Game::MAIN_MENU;

	Game2D::ScreenCoord::init(screenWidth, screenHeight);
	currentLevel = 0;
}

void Game::loadLevelsFromFile()
{
	//on linux the directorys  are in a random order will need to read in all levels sort them then load in the levels
	std::vector<std::string> dirs;
	for (auto it : std::filesystem::directory_iterator("levels")) {
		dirs.push_back(it.path().string());
	}
	try {
		std::sort(dirs.begin(), dirs.end());
	}
	catch (std::exception e) {
		std::cerr << e.what() << "\n";
		exit(-1);
	}
	
	//for (auto it : std::filesystem::directory_iterator("levels")) {
	for(auto it : dirs)	{
		levels.push_back(Level());

		std::ifstream levelFile;
		levelFile.open(it);

		std::cout << it << "\n";

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
		*2 - moving platform
		*3 - sprite
		*4 - enemy
		*5 - no rotate zone
		*/
		while (std::getline(levelFile, line)) {
			//std::cout << "Reading new line\n";
			float a, b, c, d, e, f, g, h, i, j;
			switch (line[0])
			{
			case '0':				
				std::sscanf(line.c_str(), "%f %f %f %f %f", &e, &a, &b, &c, &d);
				levels.back().addWall(Game2D::Rect(a, b, c, d));
				break;
			case '1':
				std::sscanf(line.c_str(), "%f %f %f %f %f", &e, &a, &b, &c, &d);
				levels.back().addKillPlane(Game2D::Rect(a, b, c, d));
				break;
			case '2':
			{
				std::sscanf(line.c_str(), "%f %f %f %f %f %f %f %f %f", &e, &a, &b, &c, &d, &f, &g, &h, &i);
				MovingPlatform platform(Game2D::Rect(a, b, c, d), Game2D::Pos2(g, h),f,i);
				//platform.setEndPos(Game2D::Pos2(g, h));
				//platform.setTravelTime(f);
				levels.back().addMovingPlatform(platform);
				break;
			}
			case '3':
				std::sscanf(line.c_str(), "%f %f %f %f %f %f %f %f %f %f", &e, &a, &b, &c, &d, &f, &g, &h, &i, &j);
				levels.back().addSprite(Game2D::Rect(a, b, c, d), Game2D::Rect(f, g, h, i), (Level::SpriteFlip)((int)j));
				break;
			case '4':
			{
				std::sscanf(line.c_str(), "%f %f %f %f %f %f %f %f %f %f", &e, &a, &b, &c, &d, &f, &g, &h, &i, &j);
				//levels.back().addEnemy(Game2D::Pos2(a, b)); 
				Enemy temp(Game2D::Pos2(a, b), Game2D::Pos2(d, f),c, (Enemy::Type)((int)i));
				//temp.setEndPos(Game2D::Pos2(d, f));
				//temp.setTravelTime(c);
				temp.setHead((Enemy::Direction)((int)(g)));
				temp.setAttackRadius(h);
				temp.setAttackSpeed(j);
				levels.back().addEnemy(temp);
				//std::cout << "Enemy start" << a << ", " << b << " end " << d << ", " << f << " speed " << c << " type " << i << " head " << g << " radius " << h << "\n";
				break;
			}
			case '5':
				std::sscanf(line.c_str(), "%f %f %f %f %f", &e, &a, &b, &c, &d);
				levels.back().addNoRotateZone(Game2D::Rect(a, b, c, d));
				break;
#if _DEV
			case '!':
				//comment I want printed out (use # for a comment in the file
				//std::sscanf()
				//print out the line sans the '!'
				std::cout << line.substr(1, line.size() - 1) << "\n";
#endif // _DEV
			}
		}
	}
#ifdef _DEV
	std::cout << levels.size() << " levels loaded\n";
#endif // _DEV
}

void Game::readDisplayConfig()
{
	std::ifstream file;
	file.open("options.rgo");

	if (!file.is_open()) {
		screenWidth = 1280;
		screenHeight = 720;
		windowHintFlags = 0;

		//glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
	}
	file >> screenWidth;
	file >> screenHeight;
	int temp;
	file >> temp;
	windowHintFlags |= (temp ? 1 << 0 : 0 << 0);
	//glfwWindowHint(GLFW_MAXIMIZED, temp);

	file.close();
}

void Game::writeDisplayConfig()
{
	std::ofstream file;
	file.open("options.rgo");

	if (!file.is_open()) {
		std::cerr << "[ERROR] Couldn't write options to file" << std::endl;
	}
	file << screenWidth << " " << screenHeight << "\n";
	file << glfwGetWindowAttrib(window, GLFW_MAXIMIZED) << "\n";

	file.close();
}

void Game::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.118f, 0.118f, 0.118f,1.0f);
	glLoadIdentity();

	/*
	glMatrixMode(GL_COLOR);
	glLoadIdentity();

	std::vector<GLfloat> colourModMat(4 * 4, 0);
	colourModMat[1] = 1;
	colourModMat[4] = 1;
	colourModMat[10] = 1;
	colourModMat[15] = 1;
	
	glMultMatrixf(&colourModMat[0]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/



	switch (currentState)
	{
		case PLAYING:
			levels.at(currentLevel).draw();
			break;
		case PAUSED:
		{
			levels.at(currentLevel).draw();
			Game2D::Sprite tempSprite(Game2D::Rect(0, 0, 100 * Game2D::ScreenCoord::getAspectRatio(), 100));
			tempSprite.setColour(Game2D::Colour(0, 0, 0, 0.5f));
			tempSprite.draw();
			pauseMenu.draw();
			break;
		}
		case LEVEL_SELECT:
			levelSelect.draw();
			break;
		case MAIN_MENU:
			mainMenu.draw();
			break;
		case OPTIONS_MENU:
			optionsMenu.draw();
			break;
		case VICTORY:
			break;
		case LOSS:
			loseScreen.draw();
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
#ifdef _DEV
	Debug::setColourBlindFilter(Debug::NORMAL);
	Debug::setDrawHitBoxes(false);
#endif // _DEV

	glfwSetWindowSizeCallback(window, resize_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	//mouseButtons.insert(std::pair<int,Game2D::KeyState>(GLFW_MOUSE_BUTTON_LEFT,Game2D::KeyState()));
	//previousMouseStates.insert(std::pair<int,Game2D::KeyState::State>(GLFW_MOUSE_BUTTON_LEFT,Game2D::KeyState::UP));

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
	Game2D::Font::insert(3);
	Game2D::Font::insert(6);
	Game2D::Font::insert(20);
	Game2D::Font::insert(40);
	Game2D::Font::initFonts();
	//!fonts

	//textures
	TextureManager::loadTextures("textures/buttonSprites.png", 1);
	TextureManager::loadTextures("textures/LevelSelectSprites.png", 2 ,GL_NEAREST);
	TextureManager::loadTextures("textures/LevelSprites.png", 3);
	//!textures

	//paused = false;
	mainMenu.init();
	optionsMenu.init();
	pauseMenu.init();
	loseScreen.init();

	//Key actions
	inputManager.addAction(Level::PLAYER_LEFT, GLFW_KEY_A);
	inputManager.addAction(Level::PLAYER_RIGHT, GLFW_KEY_D);
	inputManager.addAction(Level::PLAYER_JUMP, GLFW_KEY_W);

	inputManager.addAction(Level::ROTATE_CLOCKWISE, GLFW_KEY_E);
	inputManager.addAction(Level::ROTATE_ANTICLOCKWISE, GLFW_KEY_Q);

	inputManager.addAction(Level::RESET, GLFW_KEY_R);
	inputManager.addAction(Level::PAUSE, GLFW_KEY_ESCAPE);
	mouseButtons.addAction(LEFT_MOUSE, GLFW_MOUSE_BUTTON_LEFT);
#ifdef _DEV
	inputManager.addAction(-10, GLFW_KEY_LEFT_SHIFT);
	inputManager.addAction(-10, GLFW_KEY_RIGHT_SHIFT);
	inputManager.addAction(-11, GLFW_KEY_LEFT_CONTROL);
	inputManager.addAction(-11, GLFW_KEY_RIGHT_CONTROL);
	inputManager.addAction(-1, GLFW_KEY_1);
	inputManager.addAction(-2, GLFW_KEY_2);
	inputManager.addAction(-3, GLFW_KEY_3);
	inputManager.addAction(-4, GLFW_KEY_4);
	inputManager.addAction(-99, GLFW_KEY_0);
	inputManager.addAction(-101, GLFW_KEY_F1);
#endif // _DEV

	//!Key actions

	levelSelect.init(levels.size());
}

void Game::resize_callback(GLFWwindow* window, int width, int height)
{
	screenWidth = width;
	screenHeight = height;
	glViewport(0, 0, width, height);
	Game2D::ScreenCoord::init(width, height);
	Game2D::ScreenCoord::alignCentre();
	Game2D::Font::init(height);
	Game2D::Font::initFonts();
}

void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//std::cout << key << " " << action << "\n";
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
	//std::cout << "mouse button callback\n";
	//std::cout << button << " " << action << "\n";
	/*
	try
	{
		if(action == GLFW_PRESS) mouseButtons.update(button,true);
		else if(action == GLFW_RELEASE) mouseButtons.update(button,false);
	}catch(...) {}*/
	try
	{
		if (action == GLFW_PRESS) {
			mouseButtons.updateKeys(button, true);
			mouseButtons.update();//update the input manager so we know a mouse button is down during the update function
		} else if (action == GLFW_RELEASE) {
			mouseButtons.updateKeys(button, false);
		}
		//if(action == GLFW_PRESS) mouseButtons.at(button).update(true);
		//else if(action == GLFW_RELEASE) mouseButtons.at(button).update(false);
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
	/*
	for(auto it = previousMouseStates.begin(); it != previousMouseStates.end();it++)
	{
		if (it->second == Game2D::KeyState::RELEASED)
			mouseButtons.at(it->first).update(false);

		it->second = mouseButtons.at(it->first).getState();
	}
	*/
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
	inputManager.update();
	//std::cout << "mouse button manager update\n";
	//mouseButtons.update();
#ifdef _DEV
	if (inputManager.getAction(-10) == InputManager::DOWN) {
		if (inputManager.getAction(-11) == InputManager::DOWN) {
			if (inputManager.getAction(-99) == InputManager::DOWN) { Debug::setColourBlindFilter(Debug::NORMAL); }
			if (inputManager.getAction(-1) == InputManager::DOWN) { Debug::setColourBlindFilter(Debug::PROTANOPIA); }
			if (inputManager.getAction(-2) == InputManager::DOWN) { Debug::setColourBlindFilter(Debug::DEUTERANOPIA); }
			if (inputManager.getAction(-3) == InputManager::DOWN) { Debug::setColourBlindFilter(Debug::TRITANOPIA); }
			if (inputManager.getAction(-4) == InputManager::DOWN) { Debug::setColourBlindFilter(Debug::ACHROMATOPSIA); }
		} else {
			if (inputManager.getAction(-99) == InputManager::DOWN) { Debug::setColourBlindFilter(Debug::NORMAL); }
			if (inputManager.getAction(-1) == InputManager::DOWN) { Debug::setColourBlindFilter(Debug::PROTANOMALY); }
			if (inputManager.getAction(-2) == InputManager::DOWN) { Debug::setColourBlindFilter(Debug::DEUTERANOMALY); }
			if (inputManager.getAction(-3) == InputManager::DOWN) { Debug::setColourBlindFilter(Debug::TRITANOMALY); }
			if (inputManager.getAction(-4) == InputManager::DOWN) { Debug::setColourBlindFilter(Debug::ACHROMATOMALY); }
		}
	}
	if (inputManager.getAction(-101) == InputManager::DOWN && inputManager.getAction(-10) == InputManager::DOWN) {
		Debug::setDrawHitBoxes(true);
	}
	if (inputManager.getAction(-101) == InputManager::DOWN && inputManager.getAction(-11) == InputManager::DOWN) {
		Debug::setDrawHitBoxes(false);
	}
	if (inputManager.getAction(-11) == InputManager::DOWN && inputManager.getAction(Level::RESET) == InputManager::DOWN) {
		levels.clear();
		loadLevelsFromFile();
		if (!(currentLevel < levels.size())) {
			currentState = MAIN_MENU;
		} else { levels.at(currentLevel).init(); }
	}
#endif // _DEV

	switch (currentState)
	{
		case PLAYING:

			if (inputManager.getAction(Level::PAUSE) == InputManager::WAS_DOWN) {
				//paused = true;;
				currentState = PAUSED;
			}
			//testLevel.update(inputManager);
			switch (levels.at(currentLevel).update(inputManager)) {
			case 1:
				if (++currentLevel == levels.size()) {
					currentState = MAIN_MENU;
					currentLevel = 0;
					break;
				}
				//
				//inputManager.setAllFalse();
				levels.at(currentLevel).setActionLockOut(inputManager);
				levels.at(currentLevel).init();
				break;
			case 2:
				currentState = LOSS;
				//YOU DIED
			default:
				break;
			}
			break;
		case PAUSED:
			if (inputManager.getAction(Level::PAUSE) == InputManager::WAS_DOWN) {
				//paused = true;;
				currentState = PLAYING;
				levels.at(currentLevel).unPause();
			} else {
				processPauseMenu();
			}
			break;
		case LEVEL_SELECT:
		{
			int result = levelSelect.update(mousePos, (Game2D::KeyState::State)mouseButtons.getAction(LEFT_MOUSE)/*mouseButtons.at(GLFW_MOUSE_BUTTON_LEFT).getState()Game2D::KeyState::UP*/, 1);
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
			processOptionsMenu();
			break;
		case VICTORY:
			break;
		case LOSS:
			loseScreen.update(mousePos, (Game2D::KeyState::State)mouseButtons.getAction(LEFT_MOUSE), 1);
			switch (loseScreen.getResult()) 
			{
			case 0:
				break;
			case 1:
				levels.at(currentLevel).init();
				levels.at(currentLevel).update(inputManager);
				currentState = PLAYING;
				break;
			case 2:
				currentState = MAIN_MENU;
				break;
			case 3:
				currentState = QUITTING;
				break;
			}
			break;
		case QUITTING:
			break;
		default:
			std::cerr << "We're in an invalid game state" << std::endl;
			break;
	}

	mouseButtons.update();//now we have processed all the mouse buttons check to see if they have changed
}

bool Game::createWindow()
{
	//readDisplayConfig();

	if (!glfwInit())
	{
		std::cerr << "failed to init glfw with error: 0x" << std::hex << std::setw(8) << std::setfill('0') << glfwGetError(NULL) << "\n";
		return false;
	}

	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
	glfwWindowHint(GLFW_MAXIMIZED, windowHintFlags & (1 << 0));

	/* Create a windowed mode window and its OpenGL context */
#if _DEV
	window = glfwCreateWindow(screenWidth, screenHeight, "Rotate - Developer Build", NULL, NULL);
#else
	window = glfwCreateWindow(screenWidth, screenHeight, "Rotate", NULL, NULL);
#endif //_DEV
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

void Game::resize(float width, float height)
{
	//int maximized = glfwGetWindowAttrib(window, GLFW_MAXIMIZED);
	//std::cout << maximized << "\n";
	glfwSetWindowSize(window, width, height);
	glViewport(0, 0, width, height);
	Game2D::ScreenCoord::init(width,height);
	Game2D::ScreenCoord::alignCentre();
	display();
}

void Game::processMainMenu()
{
	mainMenu.update(mousePos, (Game2D::KeyState::State)mouseButtons.getAction(LEFT_MOUSE)/*mouseButtons.at(GLFW_MOUSE_BUTTON_LEFT).getState()Game2D::KeyState::UP*/, 1);
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

void Game::processOptionsMenu()
{
	optionsMenu.update(mousePos, (Game2D::KeyState::State)mouseButtons.getAction(LEFT_MOUSE), 1);

	switch (optionsMenu.getResult(resize))
	{
	case 1:
	case 2:
		currentState = MAIN_MENU;
		break;
	default:
		break;
	}
}

void Game::processPauseMenu()
{
	pauseMenu.update(mousePos, (Game2D::KeyState::State)mouseButtons.getAction(LEFT_MOUSE)/*mouseButtons.at(GLFW_MOUSE_BUTTON_LEFT).getState() Game2D::KeyState::UP*/, 1);
	switch (pauseMenu.getResult())
	{
	case 1:
		//testLevel.init();
		//levels.at(currentLevel).init();
		//currentState = LEVEL_SELECT;
		//currentState = PLAYING;
		//rrstd::cout << "Unpause\n";
		currentState = PLAYING;
		levels.at(currentLevel).unPause();
		break;
	case 2:
		currentState = MAIN_MENU;
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

	writeDisplayConfig();

	glfwTerminate();

//	Game2D::Font::clear();

	return 0;
}