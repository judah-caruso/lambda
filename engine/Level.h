#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "MapLoader/MapLoader.h"

class Level
{
private:
	bool DEBUG_MODE = false;

	std::string map_name;
	std::string file_name;
	
public:
	Grid* grid = nullptr;

	Level(bool DEBUG, std::string fname);
	~Level();

	void unload_all();
	void update();
	void render();
	void print_info();
};

#endif // LEVEL_H