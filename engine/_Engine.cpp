#include "_Engine.h"

Game* game = nullptr;

int main() {	
	log_debug_clear_previous();
	game = new Game("HPR(oguelike)");
	
	LE_Error err = game->init(true);
	if (err.has_error()) {
		log_debug(err.get_status());
		log_error("Unable to initialize game! Reason: " + err.get_status());
		return 1;
	}

	return 0;
}
