#pragma once
#ifndef LECELL_H
#define LECELL_H

#include <string>

enum CellType {
	WALL,
	FLOOR,
	ENTITY,
	PLAYER_SPAWN,
};

extern enum CellType celltype;

CellType convert_type(std::string str);

#endif // LECELL_H
