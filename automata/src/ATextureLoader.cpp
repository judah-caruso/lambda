#include "ATextureLoader.hpp"

std::optional<ATexture> create_texture(const char* file) {
	GLuint id = SOIL_load_OGL_texture(
		file,
		SOIL_LOAD_AUTO, 
		SOIL_CREATE_NEW_ID,
		0
		//SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	if (id == 0) {
		return std::optional<ATexture>();
	}

	int width; int height;
	glGetTextureLevelParameteriv(id, 0, GL_TEXTURE_WIDTH, &width);
	glGetTextureLevelParameteriv(id, 0, GL_TEXTURE_HEIGHT, &height);

	return ATexture{id, file, width, height};
}

std::optional<ATexture> create_texture(const char* file, unsigned int flags) {
	GLuint id = SOIL_load_OGL_texture(
		file,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		flags
	);

	if (id == 0) {
		return std::optional<ATexture>();
	}
	
	return ATexture{ id, file };
}

void unload_texture(ATexture* texture) {
	SOIL_free_image_data((unsigned char*)texture->id);
}
