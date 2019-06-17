#include "ASerializer.hpp"



ASerializer::ASerializer(){}

ASerializer::~ASerializer(){}


toml_layer ASerializer::make_layer() {
	return std::vector<toml::table>{"map_layer", {}};
}
	
void add_tile_to_layer(toml_layer layer, toml_tile tile) {
	layer[0].at("map_layer").as_array().push_back(tile);
}


toml_tile ASerializer::to_toml_tile(const char* t, ImVec4 world_pos, ImVec4 tile_pos, std::vector<const char*> flags) {
	toml::table table = toml::table{
		{{"type", t},
		{"pos_world", toml::array{world_pos.x, world_pos.y, world_pos.w, world_pos.z}},
		{"pos_tile", toml::array{tile_pos.x, tile_pos.y, tile_pos.w, tile_pos.z}},
		{"flags", toml::array{} }} };

	if (flags.size() > 0) {
		for (const char* flag : (std::vector<const char*>)flags) {
			table.at("flags").as_array().push_back(flag);
		}
	}

	return table;
}
