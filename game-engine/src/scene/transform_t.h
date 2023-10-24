#pragma once
#include "glm/glm.hpp"

class transform_t
{
public:

	transform_t();
	transform_t(const glm::f32vec2& position, const glm::f32vec2& scale, float rotation);
	
	void set_position(const glm::f32vec2& position);
	void set_scale(const glm::f32vec2& scale);
	void set_rotation(float rotation);

	const glm::f32vec2& position() const { return m_position; }
	const glm::f32vec2& scale() const { return m_scale; }
	float rotation() const { return m_rotation; }


	glm::mat4 transform();
private:
	void update_transform();

	glm::mat4 m_cache;
	glm::f32vec2 m_position;
	glm::f32vec2 m_scale;
	float m_rotation;
};