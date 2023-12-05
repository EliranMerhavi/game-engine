#include "pch.h"
#include "forces.h"

glm::f32vec2 mutualGravity(game_object_t obj1, game_object_t obj2, float strength)
{
	glm::f32vec2 pos1 = obj1.get<component::transform>().position();
	glm::f32vec2 pos2 = obj2.get<component::transform>().position();

	glm::f32vec2 rvec = pos2 - pos1;
	return (strength * obj1.get<component::rigidBody>().mass * obj2.get<component::rigidBody>().mass /glm::dot(rvec, rvec)) * rvec;
}


