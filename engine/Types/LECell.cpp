#include "LECell.h"

CellType convert_type(std::string str) {
	if (str == "ent_floor")			return FLOOR;
	if (str == "ent_wall")			return WALL;
	if (str == "ent_player_spawn")	return PLAYER_SPAWN;
	if (str == "ent_default")		return ENTITY;

	throw "Unknown entity type: " + str;
}

