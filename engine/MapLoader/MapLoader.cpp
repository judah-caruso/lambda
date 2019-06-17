#include "MapLoader.h"

MapLoader::MapLoader(std::string filename) {
	const toml::table& map_file = toml::parse(filename);

	const toml::table& map_metadata				= toml::get<toml::table>(map_file.at("map_metadata"));
	const toml::table& map_info					= toml::get<toml::table>(map_file.at("map_info"));
	const std::vector<toml::table>& map_layers	= toml::get<std::vector<toml::table>>(map_file.at("map_layer"));

	MapData* map_data		= new MapData{};
	map_data->name			= map_metadata.at("name").as_string();
	map_data->tileset		= map_metadata.at("tileset").as_string();
	map_data->asset_path	= map_metadata.at("asset_path").as_string();

	// most likely will be refactored in the future to use a temp size_thing variable
	map_data->size_map  = { (int)map_info.at("size_map").as_array()[0].as_integer(),  (int)map_info.at("size_map").as_array()[1].as_integer() };
	map_data->size_tile = { (int)map_info.at("size_tile").as_array()[0].as_integer(), (int)map_info.at("size_tile").as_array()[1].as_integer() };
	
	map_data->flags		= toml::get<std::vector<std::string>>(map_info.at("flags"));


	map_name = map_data->name;
	map_grid = new Grid(map_data->size_map.first, map_data->size_map.second, map_data->size_tile.first, map_data->size_tile.second);
	Texture2D temp_tex;

	std::string tileset_path_full = map_data->asset_path + map_data->tileset;
	std::cout << "Path: " + tileset_path_full << std::endl;

	temp_tex = LoadTexture(tileset_path_full.c_str());
	map_grid->set_tileset(temp_tex);

	// use for layers
	int current_layer = 0;
	int n_layers = map_layers.size();
	
	for (toml::table layer : map_layers) {
		// skip our initializer layer
		std::string& layer_type = toml::get<std::string>(layer.at("type"));
		if (layer_type == "nil") continue;	
		
		std::vector<toml::table> layer_tiles = toml::get<std::vector<toml::table>>(layer.at("tiles"));
		for (toml::table tile : layer_tiles) {

			// should be refactored in the future so cell initialization happens first,
			// then we fill it with the proper information
			CellType _type = convert_type(tile.at("type").as_string());
			int _width = tile.at("pos_world").as_array()[2].as_integer();
			int _height = tile.at("pos_world").as_array()[3].as_integer();

			Cell* cell = new Cell{_type, {(float)_width, (float)_height}};
			cell->rec_bounding.x = tile.at("pos_world").as_array()[0].as_integer();
			cell->rec_bounding.y = tile.at("pos_world").as_array()[1].as_integer();
			cell->rec_texture.x = tile.at("pos_tile").as_array()[0].as_integer();
			cell->rec_texture.y = tile.at("pos_tile").as_array()[1].as_integer();
			cell->rec_texture.width = tile.at("pos_tile").as_array()[2].as_integer();
			cell->rec_texture.height = tile.at("pos_tile").as_array()[3].as_integer();
			

			if (layer_type == "entities" && tile.at("type") == "ent_player_spawn") {
				map_grid->set_initial_cell({ cell->rec_bounding.x, cell->rec_bounding.y });
			}

			// finally check if we have any valid flags
			for (auto flag : tile.at("flags").as_array()) {
				cell->check_flag(flag.as_string());
			}

			// once we're done, push or cell into our grid
			int coord_x = cell->rec_bounding.x / _width;
			int coord_y = cell->rec_bounding.y / _height;
			map_grid->set_cell(layer_to_int(layer_type), coord_x, coord_y, cell);
		}

		current_layer += 1;
	}

	//UnloadTexture(temp_tex);
	delete(map_data);
}

// refactor (possible enum?)
int MapLoader::layer_to_int(std::string layer) {
	if (layer == "floor") return 0;
	if (layer == "walls") return 1;
	if (layer == "entities") return 2;

	throw "Invalid layer type: " + layer;
}

MapLoader::~MapLoader()
{
}
