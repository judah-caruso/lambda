#include "Editor.hpp"

Editor::Editor(const char* wname, SDL_Window* win, SDL_Renderer* ren) : AGuiBase(wname) { 
	window = win;
	renderer = ren;

	for (int i = 0; i < 1; i++) {
		//boost::multi_array<Cell*, 2> tmp(boost::extents[_map_size.x][_map_size.y]);
		//layers.push_back(tmp);
		Layer tmp{"Layer", true, boost::multi_array<Cell*, 2>(boost::extents[_map_size.x][_map_size.y])};
		layers.push_back(tmp);
	}

	//set_window_flag(ImGuiWindowFlags_NoResize);
	set_window_flag(ImGuiWindowFlags_NoBringToFrontOnFocus);
	set_window_flag(ImGuiWindowFlags_NoTitleBar);
}

Editor::~Editor(){}

void Editor::apply_window_styling() {
	//set_style_var(ImGuiStyleVar_WindowMinSize, ImVec2(768, 768));
};

int Editor::align(int v) {
	return v & -_cell_size;
	//return v & 0xffe0; // 1111111111100000 (-32) 
}

ImVec2 Editor::align(ImVec2 vec) {
	return ImVec2((int)vec.x & 0xffe0, (int)vec.y & 0xffe0);
}

ImVec2 operator+(ImVec2 left, ImVec2 right) { return ImVec2(left.x + right.x, left.y + right.y); }
ImVec2 operator+(ImVec2 left, int right)	{ return ImVec2(left.x + right, left.y + right); }
ImVec2 operator*(ImVec2 left, int right)	{ return ImVec2(left.x * right, left.y * right); }
ImVec2 operator*(ImVec2 left, ImVec2 right)	{ return ImVec2(left.x * right.x, left.y * right.y); }
ImVec2 operator-(ImVec2 left, ImVec2 right) { return ImVec2(left.x - right.x, left.y - right.y); }
ImVec2 operator-(ImVec2 left, int right)	{ return ImVec2(left.x - right, left.y - right); }
bool operator<=(ImVec2 left, int right)		{ return left.x <= right && left.y <= right; }

ImVec2 get_scroll() { return ImVec2(ImGui::GetScrollX(), ImGui::GetScrollX()); }

void resize_window(ImGuiSizeCallbackData* data) {
	std::cout << (bool)data << std::endl;
}

ASerializer serializer = ASerializer{};


void Editor::open_import_texture_modal() {
	nfdchar_t* path = nullptr;
	nfdresult_t status = NFD_OpenDialog("png,jpeg,jpg,tiff", 0, &path);

	if (status == NFD_ERROR) {
		ImGui::BeginPopup("Import texture");
		ImGui::Text(NFD_GetError());
		if (ImGui::Button("Close")) {
			ImGui::EndPopup();
			return;
		}

		ImGui::EndPopup();
		return;
	}

	if (status == NFD_OKAY) {
		std::filesystem::path mutable_path((char*)path);

		ATexture texture = *create_texture(mutable_path.string().c_str());
		if (texture.id == 0) {
			ImGui::BeginPopup("Import texture");
			ImGui::Text("Unable to load texture '%s'", mutable_path.c_str());
			if (ImGui::Button("Close")) {
				ImGui::EndPopup();
				return;
			}

			ImGui::EndPopup();
			return;
		}

		_loaded_textures.push_back(texture);
		_current_texture = texture;
	}
}


bool properties_modal_opened = false;
void Editor::render_side_menu() {
	ImGuiWindowFlags option_flags = ImGuiWindowFlags_AlwaysAutoResize;

	ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiCond_Always);
	if (!ImGui::Begin("Options", NULL, option_flags)) {
		ImGui::End();
		return;
	}

	if (ImGui::CollapsingHeader("Tileset")) {
		if (ImGui::Button("Import tileset")) {
			open_import_texture_modal();
		}

		ImGui::Separator(); ImGui::Spacing();

		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImVec2 canvas_pos = ImGui::GetCursorScreenPos();     
		ImVec2 canvas_size = ImVec2(ImGui::GetWindowSize().x, 256);
		//ImVec2 canvas_size = ImGui::GetContentRegionAvail();
		mouse_pos = ImVec2(ImGui::GetIO().MousePos.x - canvas_pos.x, ImGui::GetIO().MousePos.y - canvas_pos.y);

		ImGui::InvisibleButton("click_handler", canvas_size);
		//draw_list->AddRectFilled(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), IM_COL32(25, 25, 25, 255));
		draw_list->PushClipRect(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), true);      // clip lines within the canvas (if we resize it, etc.)
		draw_list->AddRectFilled(canvas_pos, canvas_pos + canvas_size, IM_COL32(25, 25, 25, 255));
		
		for (auto texture : _loaded_textures) {
			draw_list->AddImage((void*)texture.id, canvas_pos, ImVec2(canvas_pos.x + texture.width, canvas_pos.y + texture.height));
		}

		// draw grid
		if (_loaded_textures.size() > 0) {
			for (int y = 0; y < canvas_size.y / _cell_size; y++) {
				for (int x = 0; x < canvas_size.x / _cell_size; x++) {
					draw_list->AddRect(ImVec2(canvas_pos.x + _cell_size * x, canvas_pos.y), ImVec2(canvas_pos.x + _cell_size * x, canvas_pos.y + canvas_size.y), IM_COL32(0, 0, 128, 255));
					draw_list->AddRect(ImVec2(canvas_pos.x, canvas_pos.y + _cell_size * y), ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + _cell_size * y), IM_COL32(0, 0, 128, 255));
				}
			}
		}

		if (_loaded_textures.size() > 0) {
			if (ImGui::IsItemHovered(0)) {
				if (ImGui::IsMouseDown(0)) {
					ImVec2 grid_tile_position = align(mouse_pos);
					_current_texture_offset = grid_tile_position;
				}
			}
			
			draw_list->AddRect(canvas_pos + _current_texture_offset, (canvas_pos + _current_texture_offset) + _cell_size, IM_COL32(255, 255, 255, 255));
		}		

		ImGui::PopClipRect();
	}

	if (ImGui::CollapsingHeader("Layers")) {
		if (ImGui::Button("Add layer")) {
			Layer tmp{"Layer", true, boost::multi_array<Cell*, 2>(boost::extents[_map_size.x][_map_size.y])};
			layers.push_back(tmp);
		}

		ImGui::SameLine();

		if (ImGui::Button("Remove layer")) {
			if (layers.size() > 1) {
				if (_current_layer == 0) {
					layers.erase(layers.begin() + _current_layer);
				} else {
					layers.erase(layers.begin() + _current_layer);
					_current_layer -= 1;
				}
			}
		}

		ImGui::Separator(); ImGui::Spacing();
		bool visible = false;	

		for (int i = 0; i < layers.size(); i++) {
			std::string label = layers[i].name;

			if (!layers[i].visible) {
				label += " (hidden)";
			}

			if (ImGui::Selectable(label.c_str(), _current_layer == i, ImGuiSelectableFlags_AllowDoubleClick)) {
				_current_layer = i;

				if (ImGui::IsMouseDoubleClicked(0)) { // layer properties modal
					properties_modal_opened = true;
					break;
				}
			}
		}
	}

	if (properties_modal_opened) {
		ImGui::SetNextWindowPosCenter();
		ImGui::SetNextWindowSize(ImVec2(300, 100));
		std::string label = "Layer properties";

		if (ImGui::Begin(label.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar)) {
			ImGui::Checkbox("Hide layer", &layers[_current_layer].visible);

			char temp_name[256];
			strcpy_s(temp_name, layers[_current_layer].name.c_str());

			if (ImGui::InputText("", temp_name, IM_ARRAYSIZE(temp_name), ImGuiInputTextFlags_EnterReturnsTrue)) {
				layers[_current_layer].name = temp_name;
				properties_modal_opened = false;
			}

			ImGui::Spacing();
			if (ImGui::Button("Close"))
				properties_modal_opened = false;

			ImGui::End();
		}
	}

	ImGui::End();
}

void Editor::render() {

	render_side_menu();

	if (!visible) return;

	ImGui::SetNextWindowSizeConstraints(ImVec2(384, 384), ImVec2(800, 600));
	ImGui::SetNextWindowPosCenter(ImGuiCond_Always);
	ImGui::SetNextWindowContentSize(ImVec2(_width - _cell_size, _height));

	apply_window_styling();

	if (!ImGui::Begin("Editor", NULL, window_flags)) {
		clear_style_vars();
		ImGui::End();
		return;
	}

	_width = align(ImGui::GetWindowSize().x);
	_height = align(ImGui::GetWindowSize().y);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 canvas_pos = ImGui::GetCursorScreenPos();     
	ImVec2 canvas_size = ImGui::GetContentRegionAvail();
    mouse_pos = ImVec2(ImGui::GetIO().MousePos.x - canvas_pos.x, ImGui::GetIO().MousePos.y - canvas_pos.y);

	ImGui::InvisibleButton("click_handler", canvas_size);
    //draw_list->AddRectFilled(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), IM_COL32(25, 25, 25, 255));
    //draw_list->PushClipRect(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), true);      // clip lines within the canvas (if we resize it, etc.)
	draw_list->AddRectFilled(canvas_pos, canvas_pos + canvas_size, IM_COL32(25, 25, 25, 255));

	// draw placed tiles
    draw_list->PushClipRect(canvas_pos, canvas_pos + canvas_size, true);      // clip lines within the canvas (if we resize it, etc.)
	for (auto layer : layers) {
		if (!layer.visible) continue;

		for (auto cell : layer.cells) {
			for (auto tile : cell) {
				if (tile == nullptr) continue;
				ImGuiCol color = IM_COL32(255, 255, 255, 255);

				draw_list->AddImage(
					(void*)tile->texture.id,
					ImVec2(canvas_pos.x + tile->grid_pos.x, canvas_pos.y + tile->grid_pos.y),
					ImVec2(canvas_pos.x + tile->grid_pos.x + _cell_size, canvas_pos.y + tile->grid_pos.y + _cell_size),
					ImVec2(tile->tile_pos.x / _current_texture.width, tile->tile_pos.y / _current_texture.height),
					ImVec2((tile->tile_pos.x + _cell_size) / _current_texture.width, (tile->tile_pos.y + _cell_size) / _current_texture.height),
					IM_COL32(255, 255, 255, 255)
				);
			}
		}
	}

	if (ImGui::IsItemHovered(0) && _current_texture.id != 0) {
		draw_list->AddRect(canvas_pos + align(mouse_pos), (canvas_pos + align(mouse_pos)) + _cell_size, IM_COL32(255, 255, 255, 255));
		ImVec2 world_tile_position = align(mouse_pos);
		ImVec2 grid_position = ImVec2(world_tile_position.x / _cell_size, world_tile_position.y / _cell_size);
		mouse_prev = world_tile_position;
		
		if (ImGui::IsMouseReleased(0) && layers[_current_layer].visible) {
			layers[_current_layer].cells[grid_position.x][grid_position.y] = new Cell{ "ent_floor", _current_texture, world_tile_position, _current_texture_offset };
			
			//toml::table tile = serializer.to_toml_tile("ent_floor", ImVec4{ world_tile_position.x, world_tile_position.y, (float)_cell_size, (float)_cell_size }, ImVec4{ 0, 0, 32, 32 }, {});
			//map_file_string << std::setw(100) << tile << std::endl;;

			//TEST_TILES.push_back(canvas_pos - align(mouse_pos) - get_scroll());
		}
		if (ImGui::IsMouseReleased(1)) {
			layers[_current_layer].cells[grid_position.x][grid_position.y] = nullptr;
		}

		draw_list->AddImage(
			(void*)_current_texture.id,
			canvas_pos + mouse_prev,
			canvas_pos + mouse_prev + _cell_size,
			ImVec2(_current_texture_offset.x / _current_texture.width, _current_texture_offset.y / _current_texture.height),
			ImVec2((_current_texture_offset.x + _cell_size) / _current_texture.width, (_current_texture_offset.y + _cell_size) / _current_texture.height),
			IM_COL32(255, 255, 255, 100)
		);

	}

	// draw grid
	if (flag_display_grid) {
		for (int y = 0; y < _map_size.y; y++) {
			for (int x = 0; x < _map_size.x; x++) {
				draw_list->AddRect(ImVec2(canvas_pos.x + _cell_size * x, canvas_pos.y), ImVec2(canvas_pos.x + _cell_size * x, canvas_pos.y + canvas_size.y), IM_COL32(0, 0, 128, 255));
				draw_list->AddRect(ImVec2(canvas_pos.x, canvas_pos.y + _cell_size * y), ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + _cell_size * y), IM_COL32(0, 0, 128, 255));
			}
		}
	}

	ImGui::PopClipRect();

	clear_style_vars();
	ImGui::End();
}


std::string Editor::get_map_toml() {
	std::stringstream stream;
	
	for (auto layer : layers) {
		toml_layer map_layer = serializer.make_layer();

		for (auto cell : layer.cells) {
			for (auto tile : cell) {
				if (tile == nullptr) continue;
				// fix this
				serializer.add_tile_to_layer(map_layer, serializer.to_toml_tile(
					tile->type,
					ImVec4(tile->grid_pos.x, tile->grid_pos.y, _cell_size, _cell_size),
					ImVec4(tile->tile_pos.x, tile->grid_pos.y, _cell_size, _cell_size),
					{}));
			}
		}

		stream << std::setw(100) << map_layer << std::endl;
	}

	return stream.str();
}
