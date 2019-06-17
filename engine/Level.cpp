#include "Level.h"

Level::Level(bool DEBUG, std::string fname){
	file_name = fname;

	MapLoader* loader = new MapLoader(file_name);
	map_name = loader->map_name;
	grid = loader->map_grid;
	grid->set_debug(DEBUG);
}

Level::~Level(){}

void Level::update() {
	grid->update();
}

void Level::render() {
	grid->render();
}

void Level::unload_all() {
	return;
}

void Level::print_info() {}
