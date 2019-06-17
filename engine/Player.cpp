#include "Player.h"

Player::~Player() {}

void Player::init() {
	Vector2 initial_pos = grid->get_initial_cell();
	position = { 0, 0 };
	coordinates = initial_pos;
}

void Player::handle_movement(int key, Direction dir) {

	if (IsKeyPressed(key)) {
		key_history.push_back(key);
		state.push(MOVE);
	}

	// if we're moving but the key is not being pressed,
	// reset the movement timer and pop the state.
	if (state.peek() == MOVE && IsKeyUp(key)) {
		state.pop();
		movement_timer = _movement_timer_reset;
	}

	// if the key is being pressed (not held) and we can move in the target direction,
	// move in said direction.
	if (IsKeyPressed(key) && grid->request_move(this, dir)) {
		state.push(MOVE);

		switch (dir) {
		case DIRECTION_UP:
			position.y -= 1;
			coordinates.y = grid->get_grid_cell(position).y;
			break;
		case DIRECTION_DOWN:
			position.y += 1;
			coordinates.y = grid->get_grid_cell(position).y;
			break;
		case DIRECTION_LEFT:
			position.x -= 1;
			coordinates.x = grid->get_grid_cell(position).x;
			break;
		case DIRECTION_RIGHT:
			position.x += 1;
			coordinates.x = grid->get_grid_cell(position).x;
			break;
		}

		state.pop();
		return;
	}
	// otherwise if we're holding the key and we can move in the target direction,
	// decrement our timer, then move once the timer is up.
	else if (IsKeyDown(key) && grid->request_move(this, dir)) {
		movement_timer -= 1 * GetFrameTime();

		if (key_history.size() >= 3 && key_history.at(2) != key) {
			log_debug("Overflow of key_history... Clearing");
			key_history.clear();
			state.pop();
			movement_timer = _movement_timer_reset;
			return;
		}

		if (movement_timer <= 0) {
			switch (dir) {
			case DIRECTION_UP:
				position.y -= 1;
				coordinates.y = grid->get_grid_cell(position).y;
				break;
			case DIRECTION_DOWN:
				position.y += 1;
				coordinates.y = grid->get_grid_cell(position).y;
				break;
			case DIRECTION_LEFT:
				position.x -= 1;
				coordinates.x = grid->get_grid_cell(position).x;
				break;
			case DIRECTION_RIGHT:
				position.x += 1;
				coordinates.x = grid->get_grid_cell(position).x;
				break;
			}

			movement_timer = _movement_timer_reset;
			state.pop();
		}
	}
}

void Player::update() {
	handle_movement(KEY_A, DIRECTION_LEFT);
	handle_movement(KEY_D, DIRECTION_RIGHT);
	handle_movement(KEY_W, DIRECTION_UP);
	handle_movement(KEY_S, DIRECTION_DOWN);

	if (IsKeyPressed(KEY_ENTER)) {
		state.print_stack();

		if (key_history.size() <= 0) {
			std::cout << "key_history is empty." << std::endl;
		}
		else {
			for (auto key : key_history) {
				std::cout << " " << key;
			}
			std::cout << std::endl;
		}
	}
}

void Player::render() {
	DrawRectangle(coordinates.x, coordinates.y, size.x, size.y, SKYBLUE);
}
