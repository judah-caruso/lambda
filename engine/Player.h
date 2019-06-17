#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "WorldEntity.h"
#include "Grid/Grid.h"
#include "Logger/Logger.h"

/*
	TODO:
		- implement main hp drain mechanic
		- fix 3 input key bug
*/

class Player : public WorldEntity
{

private:
	Grid* grid = nullptr;
	float _movement_timer_reset = 0.08f;
	float movement_timer = _movement_timer_reset;
	std::vector<int> key_history{};

public:
	Player(Grid* _g) { grid = _g; }
	~Player();

	void init();
	void handle_movement(int key, Direction dir);
	void update();
	void render();
};

#endif // PLAYER_H

