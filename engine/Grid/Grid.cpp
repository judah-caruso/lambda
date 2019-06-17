#include "Grid.h"


Grid::Grid(int mw, int mh, int cw, int ch) {
	for (int i = 0; i < 3; i++) {
		Cell2D tmp(boost::extents[mw][mh]);
		cells.push_back(tmp);
	}
	cell_width = cw;
	cell_height = ch;
	grid_width = mw;
	grid_height = mh;
}

Grid::~Grid() {}

void Grid::update() {
}

void Grid::set_cell(int layer, int x, int y, Cell* c) { 
	if (layer > cells.size())
		throw "Invalid layer!";

	std::cout << "pushed to layer " << layer << "{" << x << ", " << y << "}" << std::endl;

	cells[layer][x][y] = c;
}

bool Grid::check_layer_position(int x, int y) {
	bool found_valid = false;

	for (auto layer : cells) {
		if (layer[x][y] == nullptr) break;
		if (layer[x][y]->is_walkable()) {
			found_valid = true;
		}
		else {
			found_valid = false;
		}
	}

	return found_valid;
}

bool Grid::request_move(WorldEntity* entity, Direction direction) {
	Vector2 entity_pos = entity->get_position();
	int x = entity_pos.x;
	int y = entity_pos.y;

	// useful but really floods the logs
	//if (DEBUG_MODE) {
	//	std::string _x = std::to_string(x);
	//	std::string _y = std::to_string(y);
	//	log_debug("Requesting move from {" + _x + ", " + _y + "}");
	//}

	switch (direction) {
	case DIRECTION_UP:
		if (y <= 0) return false;
		if (check_layer_position(x, y - 1))
			return true;
		//if (cells[0](x, y-1) != nullptr && cells(x, y - 1)->is_walkable()) return true;
		break;
	case DIRECTION_DOWN:
		if (y >= grid_height - 1) return false;
		if (check_layer_position(x, y + 1))
			return true;
		//if (cells(x, y+1) != nullptr && cells(x, y+1)->is_walkable()) return true;
		break;
	case DIRECTION_LEFT:
		if (x <= 0) return false;	
		if (check_layer_position(x - 1, y))
			return true;
		//if (cells(x-1, y) != nullptr && cells(x-1, y)->is_walkable()) return true;
		break;
	case DIRECTION_RIGHT:
		if (x >= grid_width - 1) return false;
		if (check_layer_position(x + 1, y))
			return true;
		//if (cells(x+1, y) != nullptr && cells(x+1, y)->is_walkable()) return true;
		break;
	}

	return false;
}

// FIX OVERFLOW OF SMALLER LAYERS
void Grid::render() {
	for (auto layers : cells) {
		for (auto cell : layers) {
			for (auto tile : cell) {
				if (tile != nullptr && tile->flag_nodraw == false) {
					DrawTexturePro(tileset, tile->rec_texture, tile->rec_bounding, { 0, 0 }, 0.0f, Color{ 255, 255, 255, 255 });
				}
			}
		}
	}
	/*	for (int y = 0; y < grid_height; y++) {
			for (int x = 0; x < grid_width; x++) {
				Cell* cell = cells[layer][x][y];
				if (cell->flag_nodraw == false) {
					DrawTexturePro(tileset, cell->rec_texture, cell->rec_bounding, { 0, 0 }, 0.0f, Color{ 255, 255, 255, 255 });
				}
			}
		}*/
}

