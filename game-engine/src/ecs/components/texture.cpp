#include "pch.h"
#include "texture.h"
#include "renderer2D/renderer2D_utils.h"

component::texture::texture(const std::string& filepath, bool flip_verticaly) : 
    m_texture_id(renderer2D::utils::load_texture(filepath.c_str()))
{

}

uint32_t component::texture::id() const
{
    return m_texture_id;
}
