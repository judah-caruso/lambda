#include "Game.h"

Level* level = nullptr;
Camera2D* camera = nullptr;
Player* player = nullptr;

Game::Game(std::string t) { title = t; }

Game::~Game() {}

LE_Error Game::init(bool DEBUG) {
	DEBUG_MODE = DEBUG;
	if (DEBUG_MODE) {
		SetTraceLogLevel(2);
		log_debug("Debug mode enabled.");
	}

	SetTargetFPS(120);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title.c_str());
	
	// check for any errors, return { true, "error reason" };
	
	std::string dir_exec = GetWorkingDirectory();
	std::string dir_maps = dir_exec + "/engine/_Assets/maps/";

	level = new Level(DEBUG_MODE, dir_maps + "map_001.lem");
	if (!level)
		return { true, "Unable to instantiate level map_001" };

	player = new Player(level->grid);
	if (!player)
		return { true, "Unable to instantiate player entity" };

	player->init();

	// check if player's initial coordinates were properly set by the grid
	if (player->get_coordinates().x != level->grid->get_initial_cell().x ||
		player->get_coordinates().y != level->grid->get_initial_cell().y) {
			return { true, "Player entity was unable to spawn in a proper location in the grid" };
	}

	camera = new Camera2D();
	if (!camera)
		return { true, "Unable to instantiate camera2d entity" };

	camera->zoom = 0.95f;

	while (!WindowShouldClose()) {
		update();
		render();
	}

	unload_all();
	CloseWindow();
	return {false, "Initialized successfully!"};
}

void Game::unload_all() {
	// unload all everything
	level->unload_all();
}

void Game::update() {
	level->update();
	player->update();
	camera->target.x = player->get_coordinates().x;
	camera->target.y = player->get_coordinates().y;
	camera->offset.x = -player->get_coordinates().x + SCREEN_WIDTH / 2;
	camera->offset.y = -player->get_coordinates().y + SCREEN_HEIGHT / 2;
}

void Game::render() {
	BeginDrawing();
	BeginMode2D(*camera);

	ClearBackground(Color{ 24, 24, 24, 255 });
	// -- render between these

	level->render();
	player->render();

	// -- render between these

	EndMode2D();
	
	// -- render any debug information
	if (DEBUG_MODE) {
		DrawFPS(10, 10);
	}
	
	EndDrawing();
}
