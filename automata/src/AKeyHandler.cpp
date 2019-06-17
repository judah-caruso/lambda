#include "AKeyHandler.hpp"

bool is_key_pressed(ImGuiKey key)	{ return ImGui::IsKeyPressed(ImGui::GetKeyIndex(key), false); }
bool is_key_pressed(A_Key key)		{ return ImGui::IsKeyPressed(key, false); }
bool is_key_pressed(int* key)		{ return ImGui::IsKeyPressed((int)key, false); }

bool is_key_down(ImGuiKey key)		{ return ImGui::IsKeyDown(ImGui::GetKeyIndex(key)); }
bool is_key_down(A_Key key)			{ return ImGui::IsKeyDown(key); }
bool is_key_down(int* key)			{ return ImGui::IsKeyDown((int)key); }

bool is_key_released(ImGuiKey key)	{ return ImGui::IsKeyReleased(ImGui::GetKeyIndex(key)); }
bool is_key_released(A_Key key)		{ return ImGui::IsKeyReleased(key); }
bool is_key_released(int* key)		{ return ImGui::IsKeyReleased((int)key); }
