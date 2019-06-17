#include "MenuBar.hpp"

MenuBar::MenuBar(Editor* ref) : AGuiBase("menu_bar"), editor_ref(ref) {}
MenuBar::~MenuBar(){}

void MenuBar::handle_keybinds() {
	ImGuiIO& io = ImGui::GetIO();
	if (io.KeyCtrl) {
		if (is_key_pressed(A_Key_N))					{ cb_new_map();  } // CTRL+N
		if (is_key_pressed(A_Key_O))					{ cb_open_map(); } // CTRL+O
		if (is_key_pressed(A_Key_S) && !io.KeyShift)	{ std::cout << "ctrl + s is pressed" << std::endl; }
		if (is_key_pressed(A_Key_Z) && !io.KeyShift)	{ std::cout << "ctrl + z is pressed" << std::endl; }
		if (is_key_pressed(A_Key_X))					{ std::cout << "ctrl + x is pressed" << std::endl; }
		if (is_key_pressed(A_Key_C))					{ std::cout << "ctrl + c is pressed" << std::endl; }
		if (is_key_pressed(A_Key_P))					{ std::cout << "ctrl + p is pressed" << std::endl; }
		if (is_key_pressed(A_Key_Q))					{ program_exit = true; } // CTRL+Q
		if (io.KeyShift) {
			if (is_key_pressed(A_Key_S))				{ std::cout << "ctrl + shift + s is pressed" << std::endl; }
			if (is_key_pressed(A_Key_Z))				{ std::cout << "ctrl + shift + z is pressed" << std::endl; }
		}
	}
}

void MenuBar::cb_new_map() {
	std::cout << "new map!" << std::endl;
	return;
}

void MenuBar::cb_open_map() {
	nfdchar_t* path = nullptr;
	nfdresult_t status = NFD_OpenDialog("lem", 0, &path);

	if (status == NFD_OKAY) {
		std::filesystem::path mutable_path((char*)path);

		std::cout << "filename: "	<< mutable_path.parent_path() << std::endl;
		std::cout << "path: "		<< mutable_path.filename() << std::endl;
		return;
	}

	if (status == NFD_CANCEL) {
		std::cout << "cancel pressed" << std::endl;
	} else {
		std::cout << NFD_GetError() << std::endl;
	}
	
	return;
}

void MenuBar::cb_save_map() {
	nfdchar_t* path = nullptr;
	nfdresult_t status = NFD_SaveDialog("lem", NULL, &path);

	std::cout << status << std::endl;
	if (status == NFD_OKAY) {
		std::ofstream map_file;
		map_file.open(path);
		map_file << editor_ref->get_map_toml() << std::endl;
		map_file.close();
		free(path);
	}

}

void MenuBar::cb_save_map_as() {

}

void MenuBar::render() {
	//ImGuiIO& io = ImGui::GetIO();

	if (!ImGui::BeginMainMenuBar()) {
		ImGui::End();
		clear_style_vars();
		return;
	}
	if (ImGui::BeginMenu("File", visible)) {
		if (ImGui::MenuItem("New Map...", "CTRL+N"))		{ cb_new_map(); }
		if (ImGui::MenuItem("Open Map...", "CTRL+O"))		{ cb_open_map(); }
		if (ImGui::MenuItem("Save", "CTRL+S"))				{ cb_save_map(); }
		if (ImGui::MenuItem("Save As...", "CTRL+SHIFT+S"))	{ /* cb_save_as(); */ }
		ImGui::Separator();
		if (ImGui::MenuItem("Exit", "CTRL+Q"))				{ program_exit = true;  }
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Edit")) {
		if (ImGui::MenuItem("Undo", "CTRL+Z", false, false))		{ /* cb_undo(); */ }
		if (ImGui::MenuItem("Redo", "CTRL+SHIFT+Z", false, false))	{ /* cb_undo(); */ }
		ImGui::Separator();
		if (ImGui::MenuItem("Cut", "CTRL+X"))	{ /* cb_cut(); */ }
		if (ImGui::MenuItem("Copy", "CTRL+C"))	{ /* cb_copy(); */ }
		if (ImGui::MenuItem("Paste", "CTRL+P")) { /* cb_paste(); */ }
		ImGui::EndMenu();
	}
	//ImGui::PushItemWidth(ImGui::GetWindowWidth() - ImGui::CalcItemWidth());
	//ImGui::Indent(io.DisplaySize.x - ImGui::CalcTextSize("About").x * 2);

	if (ImGui::BeginMenu("Help")) {
		if (ImGui::MenuItem("About")) { /* cb_about(); */ }
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();
}
