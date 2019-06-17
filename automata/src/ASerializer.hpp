#pragma once
#ifndef _A_SERIALIZER_H
#define _A_SERIALIZER_H

#undef min // |
#undef max // |> fixes toml lib issue
#include <toml.hpp>
#include <string>
#include <vector>
#include "imgui.h"

typedef std::vector<toml::table> toml_layer;
typedef toml::table toml_tile;

class ASerializer
{
private:

protected:


public:
	ASerializer();
	~ASerializer();

	toml_layer make_layer();
	void add_tile_to_layer(toml_layer layer, toml_tile tile);
	toml_tile to_toml_tile(const char* t, ImVec4 world_pos, ImVec4 tile_pos, std::vector<const char*> flags);
};

#endif
