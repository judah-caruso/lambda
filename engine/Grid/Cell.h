#pragma once
#ifndef CELL_H
#define CELL_H

#include "../Types/LECell.h"

class Cell
{
private:
	CellType type = WALL;
	WorldEntity* object = nullptr;

public:
	bool flag_nodraw = false;

	Cell(CellType t, Vector2 s = { 16, 16 }) 
		: type(t), size(s), rec_texture{}
	{
		rec_bounding.width = s.x;
		rec_bounding.height = s.y;
	};

	~Cell() {};

	Vector2 size;
	Rectangle rec_bounding;
	Rectangle rec_texture;

	CellType get_type() { return type;  }
	void set_type(CellType t) { type = t; }

	bool is_empty() {
		if (this->object == nullptr) return true;
		return false;
	}
	
	bool is_walkable() { 
		if (type == FLOOR && is_empty()) return true;
		return false;
	}

	void check_flag(std::string flag) {
		if (flag == "event_nodraw") flag_nodraw = true;
	}
};


#endif // CELL_H
