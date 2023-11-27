#include "pch.h"
#include "texture.h"
#include "renderer2D/renderer2D_utils.h"

component::texture::texture(const std::string& filepath, bool flip_verticaly) :
    component::texture::texture(renderer2D::utils::load_texture(filepath.c_str(), flip_verticaly))
{
}

component::texture::texture(uint32_t tex_id) :
    component::texture::texture(tex_id, {1.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f})
{

}

component::texture::texture(uint32_t tex_id, const glm::f32vec2& sub_texture_size, const glm::f32vec2& indices, const glm::f32vec2& texture_size)
    : m_texture_id(tex_id), m_coords()
{
    m_coords[0] = {};
    m_coords[1] = {};
    m_coords[2] = {};
    m_coords[3] = {};
}

uint32_t component::texture::id() const
{
    return m_texture_id;
}

const std::array<glm::f32vec2, 4>& component::texture::coords() const
{
    return m_coords;
}
