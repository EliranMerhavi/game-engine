#include "pch.h"
#include "renderer2D_utils.h"
#include "renderer2D/renderer2D.h"

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
	
	renderer2D::create_texture(texture, data, width, height);
	stbi_image_free(data);

    return texture;
}

