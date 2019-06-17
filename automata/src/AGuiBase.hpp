#pragma once
#ifndef _A_GUIBASE_H
#define _A_GUIBASE_H

#include "imgui.h"

class AGuiBase
{
private:
	int n_style_vars = 0;
	int n_win_flags = 0;

protected:
	ImGuiWindowFlags window_flags = 0;
	const char* name;
	bool visible = true;

protected:
	void set_window_flag(ImGuiWindowFlags f)					{ window_flags |= f; n_win_flags += 1; }
	void set_style_var(ImGuiStyleVar var, float val)			{ ImGui::PushStyleVar(var, val); n_style_vars += 1; }
	void set_style_var(ImGuiStyleVar var, const ImVec2& val)	{ ImGui::PushStyleVar(var, val); n_style_vars += 1; }

	void clear_style_vars() { if (n_style_vars <= 0) return; ImGui::PopStyleVar(n_style_vars); n_style_vars = 0; }

public:
	AGuiBase(const char* wname);
	~AGuiBase();

	virtual void render() {};
	virtual void apply_window_styling() {};
};

#endif
