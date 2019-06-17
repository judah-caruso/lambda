#pragma once
#ifndef _A_EDITOR_H
#define _A_EDITOR_H

#include "AGuiBase.hpp"
#include "ASerializer.hpp"
#include <SDL.h>
#include <GL/gl3w.h>
#include "nfd.h"
#include <filesystem>

#include <vector>
#include <string>
#include <sstream>
#include <boost/multi_array.hpp>
#include <algorithm> // clamp
#include <iostream>

#include "ATextureLoader.hpp"

typedef struct {
	const char* type;
	ATexture& texture;
	ImVec2 grid_pos;
	ImVec2 tile_pos;
} Cell;

typedef struct {
	std::string name = "Layer";
	bool visible = true;
	boost::multi_array<Cell*, 2> cells;
} Layer;

class Editor : protected AGuiBase
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	int _width  = 1024;
	int _height = 768;
	int _cell_size = 32;
	int _map_min_size = 1;
	int _map_max_size = 1024;
	ImVec2 _map_size = ImVec2(24, 24);

	ImVec2 mouse_pos = ImVec2(0, 0);
	ImVec2 window_size = ImVec2(0, 0);

	std::vector<ATexture> _loaded_textures;
	ATexture _current_texture;
	ImVec2 _current_texture_offset;

	int _current_layer = 0;
	std::vector<Layer> layers;
	//std::vector<boost::multi_array<Cell*, 2>> layers;

	std::string map_filename;
	std::stringstream map_file_string;

private: // private functions
	int align(int v);
	ImVec2 align(ImVec2 vec);
	void render_side_menu();

protected:
	void apply_window_styling();

public: // global editor flags
	bool flag_display_grid = true;
	void open_import_texture_modal();

public:
	Editor(const char* wname, SDL_Window* win, SDL_Renderer* ren);
	~Editor();

	int width()			{ return _width; }
	int height()		{ return _height; }
	int width(int w)	{ _width = w; }
	int height(int h)	{ _height = h; }
	
	ImVec2 mouse_prev = ImVec2(0, 0);
	ImVec2 window_pos = ImVec2(0, 0);

	void set_mouse_pos(int x, int y) { mouse_pos.x = x; mouse_pos.y = y; }
	void set_window_size(int x, int y) { window_size.x = x; window_size.y = y; }
	ImVec2 get_mouse_pos() { return mouse_pos;  }
	std::string get_map_toml();

	void render();
};

#endif // _A_EDITOR_H