#pragma once
#ifndef GAME_H
#define GAME_H

#include "Types/LEError.h"

#include "Logger/Logger.h"
#include "Level.h"
#include "Player.h"

#include <raylib.h>
#include <string>
#include <stdlib.h>
#include <iostream>

class Game
{

private:
	std::string title;
	int SCREEN_WIDTH = 800;
	int SCREEN_HEIGHT = 600;
	bool DEBUG_MODE = false;

public:
	Game(std::string t);
	~Game();

	LE_Error init(bool DEBUG);
	void unload_all();
	void update();
	void render();
};

#endif // GAME_H