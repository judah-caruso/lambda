#pragma once
#ifndef A_TEXTURELOADER_H
#define A_TEXTURELOADER_H

#include <SOIL/SOIL.h>
#include <GL/gl3w.h>
#include <optional>


typedef struct {
	GLuint id;
	const char* file;
	int width;
	int height;
} ATexture;

std::optional<ATexture> create_texture(const char* file);
std::optional<ATexture> create_texture(const char* file, unsigned int flags);

void unload_texture(ATexture* texture);

#endif // A_TEXTURELOADER_H