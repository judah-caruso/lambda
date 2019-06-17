#pragma once

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <iostream>
#include <tuple>
#include <vector>

typedef enum _state {
	IDLE,
	MOVE,
	ATTACK,
	BLOCK
} State;

class StateMachine
{
private: 
	std::vector<int> stack{};
public:
	StateMachine();
	~StateMachine();

	void print_stack();
	void push(int state);
	int pop();
	int peek();

};

#endif // STATEMACHINE_H