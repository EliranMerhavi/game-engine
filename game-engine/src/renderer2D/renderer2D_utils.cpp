#include "pch.h"
#include "renderer2D_utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

uint32_t renderer2D::utils::load_texture(const char* filepath, bool flip_verticaly)
{
	stbi_set_flip_vertically_on_load(flip_verticaly);

	uint32_t texture;
	// load and generate the texture
	int32_t width, height, nrChannels;
	uint8_t* data = stbi_load(filepath, &width, &height, &nrChannels, 4);

	if (!data)
		throw std::exception("failed to load texture");

	

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

    return texture;
}
