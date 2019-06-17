#pragma once

#ifndef WORLDENTITY_H
#define WORLDENTITY_H

#include "raylib.h"
#include "StateMachine.h"
#include <string>

class WorldEntity
{
protected:
	std::string layer{ "entities" };
	Vector2 size{ 32, 32 };
	Vector2 position{ 0, 0 };
	Vector2 coordinates{ 0, 0 };
	StateMachine state{};

public:
	WorldEntity() {};
	~WorldEntity() {};

	Vector2 get_size() { return size;  }
	Vector2 get_position() { return position; }
	Vector2 get_coordinates() { return coordinates; }

	virtual void update();
	virtual void render();
};

#endif // WORLDENTITY_H