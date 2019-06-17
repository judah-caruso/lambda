#include "StateMachine.h"

StateMachine::StateMachine() {
}

StateMachine::~StateMachine() {
}

void StateMachine::print_stack() {
	if (stack.size() <= 0) return;

	std::cout << "Stack: " << std::endl;

	for (auto state : stack) {
		std::cout << " " << state;
	}
	std::cout << std::endl;
}

void StateMachine::push(int state) {
	if (stack.size() <= 0) {
		stack.push_back(state);
		return;
	}
	auto it = stack.begin();
	it = stack.insert(it, state);
}

int StateMachine::pop() {
	// if our state machine is empty,
	// push IDLE and return a peek instead
	if (stack.size() <= 0) {
		stack.push_back(IDLE);
		return peek();
	}

	int st = stack.at(0);
	stack.erase(stack.begin());
	return st;
}

int StateMachine::peek() {
	if (stack.size() <= 0) return -1;
	return stack.at(0);
}
