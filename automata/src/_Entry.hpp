#pragma once
#ifndef _AUTOMATA_EDITOR
#define _AUTOMATA_EDITOR

#include "imgui.h"
#include "impl/imgui_impl_sdl.h"
#include "impl/imgui_impl_opengl3.h"
#include <SDL.h>
#include <GL/gl3w.h>

#include "Editor.hpp"
#include "MenuBar.hpp"

#include <iostream> // cout, cerr

#define AUTOMATA_VERSION "0.0.0"
#define AUTOMATA_NAME "Automata Editor"
#define AUTOMATA_WINDOW_TITLE AUTOMATA_NAME " " AUTOMATA_VERSION

std::string glsl_version = "";

void set_platform_gl_attributes() {
#if __APPLE__
	// GL 3.2 Core + GLSL 150
	glsl_version = "#version 150";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
	// GL 3.0 + GLSL 130
	glsl_version = "#version 130";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif
}

#endif // _AUTOMATA_EDITOR
