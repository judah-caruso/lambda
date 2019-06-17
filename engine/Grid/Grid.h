#pragma once

#ifndef GRID_H
#define GRID_H

//#include <boost/numeric/ublas/matrix.hpp>
#include <boost/multi_array.hpp>
#include <array>
#include "raylib.h"

#include "../WorldEntity.h"
#include "../Logger/Logger.h"
#include "../Types/LEDirection.h"
#include "Cell.h"

class Grid
{
private:
	bool DEBUG_MODE = false;
	typedef boost::multi_array<Cell*, 2> Cell2D;
	typedef boost::detail::multi_array::sub_array<Cell*, 1> Cell1D;
	//typedef cell_multi::index index;

	std::vector<Cell2D> cells;

	//std::map<std::string, boost::multi_array<Cell*, 2>> cells;
	Vector2 offset;
	Vector2 initial_cell;
	Texture2D tileset;

public:
	int cell_width = 32;
	int cell_height = 32;
	int grid_width;
	int grid_height;

public:
	Grid(int mw, int mh, int cw, int ch);
	~Grid();
	
	Rectangle get_grid_cell(Vector2 pos) { return cells[0][(int)pos.x][(int)pos.y]->rec_bounding; }
	
	void set_initial_cell(Vector2 pos) { initial_cell = pos; }
	Vector2 get_initial_cell() { return initial_cell; }

	void set_cell(int layer, int x, int y, Cell* c);

	void set_debug(bool DEBUG) { DEBUG_MODE = DEBUG; }
	void set_tileset(std::string fname) { tileset = LoadTexture(fname.c_str()); }
	void set_tileset(Texture2D tex) { tileset = tex; }

	bool request_move(WorldEntity* entity, Direction direction);
	bool check_layer_position(int x, int y);
	void render();
	void update();
	void unload_all() {
		UnloadTexture(tileset);
	};
};

#endif // GRID_H