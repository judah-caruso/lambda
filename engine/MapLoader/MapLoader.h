#pragma once
#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <toml.hpp>
#include <map>
#include "../Grid/Grid.h"

/*
	MAPLOADER
	---------

	MapLoader should take a Lambda Engine toml (letoml, leml) file, parse it into a Level object,
	load any assets needed by that level, and create a grid valid for said Level.

*/

typedef struct _map {
	std::string name;
	std::string tileset;
	std::string asset_path;
	std::pair<int, int> size_map;
	std::pair<int, int> size_tile;
	std::vector<std::string> flags;
} MapData;

class MapLoader
{
private:
	int layer_to_int(std::string layer);

public:
	MapLoader(std::string filename);
	~MapLoader();

	Grid* map_grid = nullptr;
	std::string map_name{};
};

#endif // MAPLOADER_H