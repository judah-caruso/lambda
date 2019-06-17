#pragma once
#ifndef _A_MENUBAR_H
#define _A_MENUBAR_H

#include "AGuiBase.hpp"
#include "AKeyHandler.hpp"
#include "Editor.hpp"

#include "nfd.h"
#include <filesystem>
#include <fstream>
#include <iostream>

class MenuBar : AGuiBase
{

private:
	Editor* editor_ref;
	bool program_exit = false;

private:
	std::string filename = "map.lem";


private:
	void cb_new_map();
	void cb_open_map();
	void cb_save_map();
	void cb_save_map_as();

public:
	MenuBar(Editor* ref);
	~MenuBar();

	void handle_keybinds();
	void render();
	
	bool program_should_exit() { return program_exit;  }
};

#endif // _A_MENUBAR_H
